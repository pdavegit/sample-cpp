#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/program_options.hpp>
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <fstream>
#include <iostream>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/file.h>
#include <log4cxx/helpers/exception.h>
#include <log4cxx/logger.h>
#include <log4cxx/propertyconfigurator.h>
#include <string>

using std::string;
using std::cerr;
using std::cout;
using std::ofstream;

string read_string_from_gz_file(const string& gz_file) {
    std::ifstream file(gz_file.c_str(), std::ios_base::in | std::ios_base::binary);
    boost::iostreams::filtering_streambuf<boost::iostreams::input> in;
    in.push(boost::iostreams::gzip_decompressor());
    in.push(file);
    std::ostringstream sstr;
    boost::iostreams::copy(in, sstr);
    return sstr.str();
}

void init_logger(const string& config_file_path)
{
    // this initializes apache log4cxx version 10.0
    // http://logging.apache.org/log4cxx
    log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("init_logger"));
    log4cxx::File config_file(config_file_path.c_str());
    log4cxx::helpers::Pool pool;
    if (config_file.exists(pool)) {
        log4cxx::PropertyConfigurator::configure(config_file);
        LOG4CXX_INFO(logger, "Configured logger from file " << config_file_path);
    } else  {
        log4cxx::BasicConfigurator::configure();
        log4cxx::Logger::getRootLogger()->setLevel(log4cxx::Level::getInfo());
        LOG4CXX_WARN(logger, "Can't file logger config file " << config_file.getName() << " Using defaults ");
    }
}

int main (int argc, char* argv[])
{
    try {
        namespace po = boost::program_options;
        po::options_description desc("Options");
        desc.add_options()
          ("help,h", "Print help message")
          ("input,i", po::value<string>()->required(), "input json file")
          ("output,o", po::value<string>()->required(), "output json file");
        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv).options(desc).run(), vm);
        if (vm.count("help")) {
            cout << "Usage: program --input input.json.gz --output output.json" << '\n';
            return 0;
        }
        po::notify(vm);
        string gz = vm["input"].as<string>();
	init_logger("./log4cxx.cfg");
        log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("main"));
        string s = read_string_from_gz_file(gz);
        LOG4CXX_INFO(logger, gz + " " + boost::lexical_cast<string>(s.size()) + " bytes");
	rapidjson::Document d;
	d.Parse(s.c_str());
	if (d.HasParseError())
	  throw "Input gz file has parse error";
	rapidjson::StringBuffer buffer;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
	d.Accept(writer);
	string output_file = vm["output"].as<string>();
	ofstream ofs = ofstream(output_file);
	if (!ofs)
	  throw string{"Cannot create output file "} + output_file;
	ofs << buffer.GetString() << '\n';
	LOG4CXX_INFO(logger, output_file + " created");
    } catch (const string& s) {
        cerr << "Exception " << s << '\n';
        return 1;
    } catch (boost::program_options::required_option& e) {
        cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    catch (std::exception& e) {
        cerr << "Exception " << e.what() << '\n';
    }
    catch (...) {
        cerr << "Unknown Exception";
        return 1;
    }
    return 0;
}
