#include "json_printer.h"

#include <iostream>
#include <stdexcept>
#include "fastcgi2/logger.h"
#include "fastcgi2/config.h"
#include "fastcgi2/stream.h"
#include "fastcgi2/handler.h"
#include "fastcgi2/request.h"
#include "fastcgi2/component.h"
#include "fastcgi2/component_factory.h"

namespace json_handler
{
class JsonHandler : virtual public fastcgi::Component, virtual public fastcgi::Handler
{
public:
	JsonHandler(fastcgi::ComponentContext *context);
	virtual ~JsonHandler();
	virtual void onLoad();
	virtual void onUnload();
	virtual void handleRequest(fastcgi::Request *req, fastcgi::HandlerContext *handlerContext);
private:
	fastcgi::Logger *logger_;
};


JsonHandler::JsonHandler(fastcgi::ComponentContext *context) : fastcgi::Component(context), logger_(NULL) {
}

JsonHandler::~JsonHandler() {
}

void
JsonHandler::onLoad() {	
	std::cout << "onLoad handler1 executed" << std::endl;
	const std::string loggerComponentName = context()->getConfig()->asString(context()->getComponentXPath() + "/logger");
	logger_ = context()->findComponent<fastcgi::Logger>(loggerComponentName);
	if (!logger_) {
		throw std::runtime_error("cannot get component " + loggerComponentName);
	}
    init_logger("/usr/app/etc/log4cxx.cfg");
}

void 
JsonHandler::onUnload() {
	std::cout << "onUnload handler1 executed" << std::endl;
}

void
JsonHandler::handleRequest(fastcgi::Request *req, fastcgi::HandlerContext *handlerContext) {
	fastcgi::RequestStream stream(req);
    string s;
    fastcgi::DataBuffer buf = req->requestBody();
    buf.toString(s);
    log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("json_handler"));
    LOG4CXX_INFO(logger, string("Input ") + boost::lexical_cast<string>(s.size()) + " bytes");
    JsonPrinter p(s);
    stream << p.print() << '\n';
	req->setStatus(200);
}

FCGIDAEMON_REGISTER_FACTORIES_BEGIN()
FCGIDAEMON_ADD_DEFAULT_FACTORY("json_handler", JsonHandler)
FCGIDAEMON_REGISTER_FACTORIES_END()
}
