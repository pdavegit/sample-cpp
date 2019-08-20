#include "json_printer.h"
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/program_options.hpp>
#include <fstream>
#include <iostream>
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
        string output_file = vm["output"].as<string>();
        ofstream ofs = ofstream(output_file);
        if (!ofs)
            throw string{"Cannot create output file "} + output_file;
        JsonPrinter p(s);
        ofs << p.print() << '\n';
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
