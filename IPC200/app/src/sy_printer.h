

#ifndef _IPRINTER_H_
#define _IPRINTER_H_

#include "base/sy_mutex.h"
#include "sy_thread.h"

#define MAX_LEN 1024
class IPrinter : public CThread
{
public:
	int getTypte();
	bool setType(int type);//0-并口，1-串口，2-网络
	int getSpeed();
	bool setSpeed(int speed);
	bool setIP(char* ip);
	IPrinter(int type);//0-输入 1-输出 2-税控服务器
	bool put(char* dat,int len);//向缓冲区写入数据
	int left(void);//剩余缓冲区大小
	int showbuf(char* dat, int len);//显示缓冲区内容，dat由调用者申请，并提供最大长度，返回实际长度
	void ThreadProc();
	bool autowelcome;
	char cip[32];

private:
	//void loop(void);//线程函数，处理缓冲区大小
	
	char cbuf[MAX_LEN];
	int rd,wr;
	bool fullflag,loopflag;
	CMutex	m_mutex;
	int ctype,cspeed;
	int mtype;//0-输入 1-输出 2-税控服务器

};

#endif
