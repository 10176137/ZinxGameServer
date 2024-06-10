#include "GameMsg.h"

// 发送报文需要消息通过创建pMsg
GameMsg::GameMsg(MSG_type _type, google::protobuf::Message* _pMsg):enMsgType(_type),pMsg(_pMsg)
{

}

// 接收报文需要对方传来序列化后的字符串进行反序列化
GameMsg::GameMsg(MSG_type _type, std::string _stream):enMsgType(_type)
{
	switch (_type)
	{
	case GameMsg::MSG_TYPE_LOGIN_ID_NAME:
		pMsg = new pb::SyncPid();
		break;
	case GameMsg::MSG_TYPE_CHAT_CONTENT:
		pMsg = new pb::Talk();
		break;
	case GameMsg::MSG_TYPE_NEW_POSITION:
		pMsg = new pb::Position();
		break;
	case GameMsg::MSG_TYPE_BROADCAST:
		pMsg = new pb::BroadCast();
		break;
	case GameMsg::MSG_TYPE_LOGOFF_ID_NAME:
		pMsg = new pb::SyncPid();
		break;
	case GameMsg::MSG_TYPE_SRD_POSITION:
		pMsg = new pb::SyncPlayers();
		break;
	default:
		break;
	}

	// 反序列化
	pMsg->ParseFromString(_stream);
}

std::string GameMsg::serialize()
{
	std::string ret;
	pMsg->SerializeToString(&ret);
	return ret;
}

GameMsg::~GameMsg()
{
	if (NULL != pMsg)
	{
		delete pMsg;
	}
}

MultMsg::~MultMsg()
{
	for (auto p : GameMsgList)
	{
		delete p;
	}
}

MultMsg::MultMsg()
{
}
