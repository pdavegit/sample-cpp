#ifndef JSON_PRINTER_H
#define JSON_PRINTER_H
#include <boost/lexical_cast.hpp>
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <string>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/file.h>
#include <log4cxx/helpers/exception.h>
#include <log4cxx/logger.h>
#include <log4cxx/propertyconfigurator.h>

using std::string;


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

class JsonPrinter
{
public:
    JsonPrinter(const string& json_in) : json_in_(json_in) {}
    string print () const {
        rapidjson::Document d;
        d.Parse(json_in_.c_str());
        if (d.HasParseError())
            throw "Input gz file has parse error";
        rapidjson::StringBuffer buffer;
        rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
        d.Accept(writer);
        string r = buffer.GetString();
        return r;
    }
private:
    string json_in_;
};

#endif
