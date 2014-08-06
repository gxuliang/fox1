/*
 * main.cpp
 *
 *  Created on: 2013-3-18
 *      Author: xul
 */

#include "base/sy_types.h"
#include "base/sy_semaphore.h"
#include "base/sy_debug.h"
#include "Manager/sy_configManager.h"
#include "rpc/sy_netrpc.h"
#include "user/sy_user.h"
#include "sy_encode.h"
#include "sy_printer.h"

#define MAX_MEDIA 3

const char * mainPath = "Config";
const char * defaultPath = "Default";
const char * EncodewPath = "/run/avfifo_w";
const char * EncoderPath = "/run/avfifo_r";
const char * MediaConfigPath = "Mediacfg";
IPrinter *gPrintOut=NULL;
//IPrinter gPrintOut;


int main(int argc, char* argv[])
{
	infof("app start!\n");
	CConfigTable aConfig;
	IConfigManager::config(mainPath, defaultPath);
	IConfigManager::instance()->getConfig("ALL", aConfig);
	IUser::instance();
	//ILog::instance();
	INetRpc::instance()->start();

	IPrinter printIn = IPrinter(0, aConfig["PrinterIn"]);//a=打印机输入，b=打印机输出
	IPrinter printOut = IPrinter(1, aConfig["PrinterOut"]);
	gPrintOut = &printOut;


	CSemaphore sem;
	sem.Pend();

	return 0;
}
