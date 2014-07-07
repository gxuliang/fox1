//
//	printer.h
//

#ifndef _PRINTER_H_
#define	_PRINTER_H_

#include “def.h”

#define	MAX_PBUF_LEN 1024

class IPrinter
{
public:
	int 	getTypte();
	bool	setType(int type);
	int 	getSpeed();
	bool 	serSpeed(int speed);

private:
	int type;
	int speed;
	uint8 sbuf[MAX_PBUF_LEN];
	uint8 rbuf[MAX_PBUF_LEN];
};

#endif
