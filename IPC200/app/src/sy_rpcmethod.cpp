/*
 * sy_rpcmthord.cpp
 *
 *  Created on: 2013-3-21
 *      Author: xul
 */

#include "base/sy_debug.h"
#include "sy_rpcmethod.h"
#include "user/sy_user.h"
#include "Manager/sy_configManager.h"

static Json::Value RPC_VER = "1.0";

bool SYRpc::Print(const Json::Value& root, Json::Value& response)
{
	std::cout << "Receive query: " << root << std::endl;
	response["jsonrpc"] = "2.0";
	response["id"] = root["id"];
	response["method"] = root["method"];
	response["result"] = "success";
	return true;
}

bool SYRpc::GetRoot(const Json::Value& root, Json::Value& response)
{
    std::cout << "Receive query: " << root << std::endl;
    response["jsonrpc"] = "2.0";
    response["id"] = root["id"];
    response["method"] = root["method"];
    response["result"] = "success";

    return true;
}


bool SYRpc::Notify(const Json::Value& root, Json::Value& response)
{
  std::cout << "Notification: " << root << std::endl;
  response = Json::Value::null;
  return true;
}

Json::Value SYRpc::GetDescription()
{
  Json::FastWriter writer;
  Json::Value root;
  Json::Value parameters;
  Json::Value param1;

  root["description"] = "Print";

  /* type of parameter named arg1 */
  param1["type"] = "integer";
  param1["description"] = "argument 1";

  /* push it into the parameters list */
  parameters["arg1"] = param1;
  root["parameters"] = parameters;

  /* no value returned */
  root["returns"] = Json::Value::null;

  return root;
}


bool SYRpc::Glogin(const Json::Value& root, Json::Value& response)
{
	Json::Value param;
	tracepoint();
	response["id"] = root["id"];

	debugf("%s-%s\n", root["params"]["version"].asCString(), "qq");// RPC_VER.asCString());
	if(root["params"]["version"] != RPC_VER)
	{
		response["result"] = "false";
		param["error"] = "VerError";
		param["session"] = Json::Value::null;
		response["params"] = param;
	}
	else
	{
		IUser::rpclogin(root, response);
	}

	return true;
}
bool SYRpc::Glogout(const Json::Value& root, Json::Value& response)
{

}

bool SYRpc::CgetConfig(const Json::Value& root, Json::Value& response)
{
	CConfigTable table;
	std::cout << "Receive query: " << root["params"]["name"] << std::endl;
	std::string name;
	name = root["params"]["name"].asString();
	infof("%s", name.c_str());
	response["id"] = root["id"];
	bool ret = IConfigManager::instance()->getConfig(name.c_str(), table);
	if(ret)
	{
		response["result"] = "true";
		response["params"][name] = table;
		std::cout << "ans " << response << std::endl;
	}
	else
	{
		response["result"] = "false";
	}

	return true;
}

#include "sy_printer.h"

extern IPrinter *gPrintOut;
bool SYRpc::getState(const Json::Value& root, Json::Value& response)
{
	CConfigTable table;
	std::cout << "Receive query: " << root["params"]["name"] << std::endl;
	std::string name;
	name = root["params"]["name"].asString();
	infof("%s", name.c_str());
	response["id"] = root["id"];

	if(root["params"]["name"] == "Buf")
	{
		char dat[MAX_LEN]="";
		int len = gPrintOut->showbuf(dat, MAX_LEN);
		infof("dat is [%s]\n", dat);
		response["params"]["name"] = name;
		response["params"]["buf"] = dat;
		response["params"]["len"] = len;
		response["params"]["pencent"] = len*10000/MAX_LEN;
		response["result"] = "true";
		std::cout << "ans " << response << std::endl;

	}
	

	return true;

}

bool SYRpc::SendCmd(const Json::Value& root, Json::Value& response)
{
	CConfigTable table;
	std::cout << "Receive query: " << root["params"]["name"] << std::endl;
	std::string name;
	name = root["params"]["name"].asString();
	infof("%s", name.c_str());
	response["id"] = root["id"];

	if(root["params"]["name"] == "TestMsg")
	{
		std::string msg;
		msg = root["params"]["data"].asString();
		gPrintOut->put(msg.c_str(), msg.length());
		response["result"] = "true";
		std::cout << "ans " << response << std::endl;

	}
	

	return true;

}
void replaceConfig(Json::Value& dest, const Json::Value& src, bool appFlag)
{
	switch ( src.type() )
	{
	case Json::nullValue:
		break;
	case Json::intValue:
	case Json::uintValue:
	case Json::realValue:
	case Json::stringValue:
	case Json::booleanValue:
		//◊∑º”∑Ω ΩªÚ’ﬂ «ƒøµƒŒƒº˛”–∂‘”¶µƒKEY£¨‘ÚÃÊªª
		if ((appFlag) || (dest.type() != Json::nullValue))
		{
			dest = src;
		}
		break;
	case Json::arrayValue:
		{
			int size = src.size();
			dest.resize(size); // Ω´ƒø±Í ˝◊È≥§∂»œﬁ÷∆Œ™‘¥ ˝◊Èµƒ≥§∂»£¨ ˝◊Èµƒƒ⁄»›»´≤øÃÊªª
			for ( int index =0; index < size; ++index )
			{
				replaceConfig(dest[index], src[index], true);
			}
		}
		break;
	case Json::objectValue:
		{
			Json::Value::Members members( src.getMemberNames() );
			for ( Json::Value::Members::iterator it = members.begin();
				it != members.end();
				++it )
			{
				const std::string &name = *it;
				//◊∑º”∑Ω ΩªÚ’ﬂ «ƒøµƒŒƒº˛”–∂‘”¶µƒKEY£¨‘ÚÃÊªª
				if ((appFlag) || (dest[name].type() != Json::nullValue))
				{
					replaceConfig(dest[name], src[name], appFlag);
				}
			}
		}
		break;
	}
}

void trimConfig(Json::Value& dest, const Json::Value& src)
{
	switch ( src.type() )
	{
	case Json::nullValue:
		break;
	case Json::intValue:
	case Json::uintValue:
	case Json::realValue:
	case Json::stringValue:
	case Json::booleanValue:
		dest = src;
		break;
	case Json::arrayValue:
		{
			int size = src.size();
			dest.resize(size); // Ω´ƒø±Í ˝◊È≥§∂»œﬁ÷∆Œ™‘¥ ˝◊Èµƒ≥§∂»
			for ( int index =0; index < size; ++index )
			{
				if (src[index].type() != Json::nullValue)
				{
					trimConfig(dest[index], src[index]);
				}
			}
		}
		break;
	case Json::objectValue:
		{
			Json::Value::Members members( src.getMemberNames() );
			for ( Json::Value::Members::iterator it = members.begin();
				it != members.end();
				++it )
			{
				const std::string &name = *it;
				if (src[name].type() != Json::nullValue)
				{
					trimConfig(dest[name], src[name]);
				}
			}
		}
		break;
	}
}



bool SYRpc::CsetConfig(const Json::Value& root, Json::Value& response)
{
	CConfigTable table, tmp;
	std::cout << "Receive query: " << root["params"]["table"] << std::endl;
	table = root["params"]["table"];
	IConfigManager::instance()->getConfig(root["params"]["name"].asCString(), tmp);

	//合并json表，把table中有变化的值覆盖到tmp中，table中没有的变量不理会
	//to do
	trimConfig(tmp, table);
	std::cout << "===" << tmp << std::endl;

	int ret = IConfigManager::instance()->setConfig(root["params"]["name"].asCString(), tmp);

	response["id"] = root["id"];
	if(ret)
	{
		response["result"] = "true";
		std::cout << "ans " << response << std::endl;
	}
	else
	{
		response["result"] = "false";
	}
	return true;
}

bool SYRpc::CgetDefault(const Json::Value& root, Json::Value& response)
{

}

bool SYRpc::CsetDefault(const Json::Value& root, Json::Value& response)
{

}

bool SYRpc::MgetMedia(const Json::Value& root, Json::Value& response)
{

}

bool SYRpc::MstopMedia(const Json::Value& root, Json::Value& response)
{

}

bool SYRpc::MCtrlMedia(const Json::Value& root, Json::Value& response)
{

}
