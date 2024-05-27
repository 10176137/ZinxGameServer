#pragma once
#include <zinx.h>
#include <google/protobuf/message.h>
#include "msg.pb.h"
class GameMsg : public UserData
{
public:
	enum MSG_type
	{
		MSG_TYPE_LOGIN_ID_NAME = 1,
		MSG_TYPE_CHAT_CONTENT = 2,
		MSG_TYPE_NEW_POSITION = 3,
		MSG_TYPE_BROADCAST = 200,
		MSG_TYPE_LOGOFF_ID_NAME = 201,
		MSG_TYPE_SRD_POSITION = 202
	}enMsgType;

	// 已知消息内容创建消息对象(发送
	GameMsg(MSG_type _type, google::protobuf::Message* _pMsg);

	// 将字节流转换成消息结构（接收
	GameMsg(MSG_type _type, std::string _stream);

	google::protobuf::Message* pMsg = NULL; 

	// 序列化本消息
	std::string serialize();

	virtual ~GameMsg();
};

class MultMsg :public UserData
{
public:
	std::list<GameMsg*> GameMsgList;
};