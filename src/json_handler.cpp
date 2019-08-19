#include <iostream>
#include <stdexcept>
#include "fastcgi2/logger.h"
#include "fastcgi2/config.h"
#include "fastcgi2/stream.h"
#include "fastcgi2/handler.h"
#include "fastcgi2/request.h"
#include "fastcgi2/component.h"
#include "fastcgi2/component_factory.h"

namespace example
{
class ExampleHandler : virtual public fastcgi::Component, virtual public fastcgi::Handler
{
public:
	ExampleHandler(fastcgi::ComponentContext *context);
	virtual ~ExampleHandler();
	virtual void onLoad();
	virtual void onUnload();
	virtual void handleRequest(fastcgi::Request *req, fastcgi::HandlerContext *handlerContext);
private:
	fastcgi::Logger *logger_;
};


ExampleHandler::ExampleHandler(fastcgi::ComponentContext *context) : fastcgi::Component(context), logger_(NULL) {
}

ExampleHandler::~ExampleHandler() {
}

void
ExampleHandler::onLoad() {	
	std::cout << "onLoad handler1 executed" << std::endl;
	const std::string loggerComponentName = context()->getConfig()->asString(context()->getComponentXPath() + "/logger");
	logger_ = context()->findComponent<fastcgi::Logger>(loggerComponentName);
	if (!logger_) {
		throw std::runtime_error("cannot get component " + loggerComponentName);
	}
}

void 
ExampleHandler::onUnload() {
	std::cout << "onUnload handler1 executed" << std::endl;
}

void
ExampleHandler::handleRequest(fastcgi::Request *req, fastcgi::HandlerContext *handlerContext) {
	fastcgi::RequestStream stream(req);
	stream << "test ok\n";
	req->setStatus(200);
}

FCGIDAEMON_REGISTER_FACTORIES_BEGIN()
FCGIDAEMON_ADD_DEFAULT_FACTORY("example", ExampleHandler)
FCGIDAEMON_REGISTER_FACTORIES_END()
}
