//
//	webservice.h
//

#ifndef _WEBSERVICE_H_
#define _WEBSERVICE_H_

#include "def.h"

class IWeb
{
public:
	IWeb(int port);
	~IWeb();
	bool start();
private:
	int port;
};

#endif
