//
//	webservice.cpp
//

#include "webservice.h"


IWeb::~IWeb()
{

}

IWeb::IWeb(int port)
{
	this->port = port;
	printf("%d\n", this->port);
}

bool IWeb::start()
{
	return true;
}