//
//	system.h
//

#ifndef _SYSTEM_H_
#define	_SYSTEM_H_

#include “def.h”

struct NetConf
{
	char ip[32];
	char netmask[32];
	char gw[32];
	char dns[32];
};

class ISyetem
{
public:
	bool getSWVer(uint8* ver);
	bool getHWVer(uint8* ver);
	bool setpasswd(uint8* passwd);

private:
	uint8 swver[64];
	uint8 hwver[64];
	uint8 pwsswd[64];//加密存储
	NetConf net;
};

#endif
