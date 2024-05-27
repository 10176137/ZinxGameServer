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

	// ��֪��Ϣ���ݴ�����Ϣ����(����
	GameMsg(MSG_type _type, google::protobuf::Message* _pMsg);

	// ���ֽ���ת������Ϣ�ṹ������
	GameMsg(MSG_type _type, std::string _stream);

	google::protobuf::Message* pMsg = NULL; 

	// ���л�����Ϣ
	std::string serialize();

	virtual ~GameMsg();
};

class MultMsg :public UserData
{
public:
	std::list<GameMsg*> GameMsgList;
};