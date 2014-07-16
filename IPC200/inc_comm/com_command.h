/*
 * com_command.h
 *
 *  Created on: 2013-4-17
 *      Author: xul
 */

#ifndef COM_COMMAND_H_
#define COM_COMMAND_H_

#include "inc_comm/com_encode.h"

typedef enum
{
	Cmdset	= 1,
	Cmdget,
	Cmdnotice,
}CmdType;

typedef enum
{
	Cmdcamg		= 1,
	Cmdencode,
}MCommand;
typedef	struct
{
	uint id;
	uint channel;//通道号，目前只有1个通道号，暂时不启用
	uint cmdtype;//1-设置；2=获取；3-通知
	uint cmd;//通过cmd识别para的结构类型
	union
	{
		CamGlobal camglo;
		EncodeCom encoder;
	}para;
}Commder;


#endif /* COM_COMMAND_H_ */
