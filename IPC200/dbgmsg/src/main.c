/*
 * main.c
 *
 *  Created on: 2013-3-14
 *      Author: xul
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

const char* ptspath = "../ptsfile";
const char* pidname = "vdd";

int main(int argc, char* argv[])
{
	char buf[32]="";
	strncpy(buf, ttyname(STDOUT_FILENO),sizeof(buf));
	printf("%s\n", buf);

	int fd = open(ptspath, O_CREAT | O_WRONLY, S_IRWXU);
	if(fd <= 0)
	{
		return -1;
	}
	write(fd, buf, strlen(buf));
	close(fd);

	int pid_id = 0;
	FILE* fp = popen("ps ax", "r");
	char lsbuf[1024]="";
	while(fgets(lsbuf, sizeof(lsbuf), fp) != NULL)
	{
		//printf("%s\n", lsbuf);
		if(strstr(lsbuf,pidname) != NULL)
		{
			printf("%s\n", lsbuf);
			char*p=NULL;
			p = strtok(lsbuf, " ");
			if(p)
			{
				printf("p = %s\n", p);
				sscanf(p, "%d", &pid_id);
				printf("%s's id is %d\n",pidname,pid_id);
				break;
			}
		}
		memset(lsbuf, 0, sizeof(lsbuf));
	}
	pclose(fp);

	kill(pid_id, SIGUSR1);

	return 0;
}
