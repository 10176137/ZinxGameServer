#pragma once
#include "GameMsg.h"
class GameChannel;
#include <zinx.h>
class GameProtocl :public Iprotocol
{
	std::string szLast;
public:
	GameProtocl();
	virtual ~GameProtocl();
	GameChannel* TcpChannel = NULL;
	// ͨ�� Iprotocol �̳�
	UserData* raw2request(std::string _szInput) override;
	std::string* response2raw(UserData& _oUserData) override;
	Irole* GetMsgProcessor(UserDataMsg& _oUserDataMsg) override;
	Ichannel* GetMsgSender(BytesMsg& _oBytes) override;
};