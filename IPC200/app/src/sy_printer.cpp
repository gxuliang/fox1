#include "sy_printer.h"


char Welcome[] = "/******************************/\r\n/*****欢迎使用打印服务系统*****/\r\n";
IPrinter::IPrinter(int type, CConfigTable& tb):m_mutex(CMutex::mutexRecursive)
{
	this->rd=0;
	this->wr=0;
	this->fullflag=false;
	this->loopflag= true;
	this->mtype = type;
	if(this->mtype == 1)//测试的是输出打印机
	{
		this->put(Welcome, sizeof(Welcome));
	}
	this->CreateThread();
}

int IPrinter::getTypte()
{
	return this->ctype;
}

bool IPrinter::setType(int type)
{
	if(type < 0 || type > 3)
	{
		return false;
	}

	this->ctype = type;
	return true;
}

int IPrinter::getSpeed()
{
	return this->cspeed;
}

bool IPrinter::setSpeed(int speed)
{
	this->cspeed = speed;
}

bool IPrinter::setIP(char* ip)
{
	strncpy(this->cip, ip, sizeof(this->cip));
}


bool IPrinter::put(char* dat,int len)
{
	if(this->left() < len)
	{
		return false;
	}
	
	for(int i=0; i < len; i++)
	{
		this->cbuf[this->wr++] = dat[i];
		wr = wr & (MAX_LEN - 1);		
	}
	
	if(this->wr == this->rd)
	{
		m_mutex.Enter();
		this->fullflag=true;//加锁处理
		m_mutex.Leave();
	}
		
	return true;
}

int IPrinter::left(void)
{
	if(this->wr > this->rd)
	{
		return (MAX_LEN - this->wr);
	}
	else if(this->wr < this->rd)
	{
		return (this->rd - this->wr);
	}
	else
	{
		return this->fullflag == true ? 0 : MAX_LEN;
	}
}


int IPrinter::showbuf(char* dat, int len)
{
	int i = 0;
	if (dat == NULL || (this->wr == this->rd && this->fullflag==false))
		return 0;
		
	for(i=0; i < len; i++)
	{
		if((this->rd+i & (MAX_LEN - 1)) == this->wr)
		{
			break;
		}
		dat[i]= this->cbuf[this->rd+i & (MAX_LEN -1)];
	}
	return i;

}

void IPrinter::ThreadProc()
{
	if(this->mtype == 0)//输入，需要读取输入打印机数据和状态
	{

	}
	else//输出，给打印机发送数据时，还需要读取打印机的状态
	{
		while(this->loopflag)
		{
			while(this->mtype == 1 &&  this->loopflag && this->left() < MAX_LEN)
			{
				printf("%c\n", this->cbuf[this->rd++]);
				this->rd = this->rd & (MAX_LEN - 1);
				m_mutex.Enter();
				this->fullflag=false;// 待加锁处理
				m_mutex.Leave();
				//usleep(1000*500);//测试代码
			}
			//读取数据
			sleep(1);
		}
	}

}