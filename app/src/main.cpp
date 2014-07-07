//
//	main.cpp
//

//#include "system.h"
//#include "printer.h"
#include "webservice.h"

const char *CONF_PATH = "config";

int main(char argc, char* argv[])
{
	//上电自检
	//注册

	/*web服务开启*/
	IWeb myWeb = IWeb(3777);
	myWeb.start();
}

//end of file
