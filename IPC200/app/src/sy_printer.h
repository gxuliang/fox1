

#ifndef _IPRINTER_H_
#define _IPRINTER_H_

#include "base/sy_mutex.h"
#include "sy_thread.h"

#define MAX_LEN 1024
class IPrinter : public CThread
{
public:
	//int 	getTypte();
	//bool	setType(int type);
	//int 	getSpeed();
	//bool 	serSpeed(int speed);
	IPrinter();
	bool put(char* dat,int len);//向缓冲区写入数据
	int left(void);//剩余缓冲区大小
	int showbuf(char* dat, int len);//显示缓冲区内容，dat由调用者申请，并提供最大长度，返回实际长度
	void ThreadProc();
private:
	//void loop(void);//线程函数，处理缓冲区大小
	
	char cbuf[MAX_LEN];
	int rd,wr;
	bool fullflag,loopflag;
	CMutex	m_mutex;
};

#endif
