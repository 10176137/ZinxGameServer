#include "GameProtocol.h"
#include <cstring>
#include "GameChannel.h"
#include "GameRole.h"
GameProtocl::GameProtocl()
{

}

GameProtocl::~GameProtocl()
{
	if (NULL != this->_gameRole)
	{
		ZinxKernel::Zinx_Del_Role(*_gameRole);
		delete _gameRole;
	}
}

UserData* GameProtocl::raw2request(std::string _szInput)
{
	MultMsg* pRet = new MultMsg();
	szLast.append(_szInput);

	// 直到szLast没有剩余的报文可以构成GameMsg
	while (1)
	{
		if (szLast.size() < 8)
		{
			return pRet;
		}

		int iLength = 0;
		iLength |= szLast[0] << 0;
		iLength |= szLast[1] << 8;
		iLength |= szLast[2] << 16;
		iLength |= szLast[3] << 24;

		// 消息格式
		int id = 0;
		id |= szLast[4] << 0;
		id |= szLast[5] << 8;
		id |= szLast[6] << 16;
		id |= szLast[7] << 24;

		if (szLast.size() - 8 < iLength)
		{
			return pRet;
		}

		// 构造报文
		GameMsg* pMsg = new GameMsg((GameMsg::MSG_type)id, szLast.substr(8, iLength));
		pRet->GameMsgList.push_back(pMsg);
		szLast.erase(0, 8 + iLength);
	}
	
	return pRet;
}

std::string* GameProtocl::response2raw(UserData& _oUserData)
{
	GameMsg* SendMesage = dynamic_cast<GameMsg*>(&_oUserData);

	std::string MsgContent = SendMesage->serialize();
	int id = SendMesage->enMsgType;
	int iLength = MsgContent.size();
	auto pret = new std::string();
	pret->push_back((iLength >> 0) & 0xff);
	pret->push_back((iLength >> 8) & 0xff);
	pret->push_back((iLength >> 16) & 0xff);
	pret->push_back((iLength >> 24) & 0xff);
	pret->push_back((SendMesage->enMsgType >> 0) & 0xff);
	pret->push_back((SendMesage->enMsgType >> 8) & 0xff);
	pret->push_back((SendMesage->enMsgType >> 16) & 0xff);
	pret->push_back((SendMesage->enMsgType >> 24) & 0xff);
	pret->append(MsgContent);
	return pret;
}

Irole* GameProtocl::GetMsgProcessor(UserDataMsg& _oUserDataMsg)
{
	return _gameRole;
}

Ichannel* GameProtocl::GetMsgSender(BytesMsg& _oBytes)
{
	return TcpChannel;
}
