#include "GameChannel.h"
#include "GameRole.h"
GameChannel::GameChannel(int _fd):ZinxTcpData(_fd)
{
}

GameChannel::~GameChannel()
{
	if (this->_protocl != NULL)
	{
		ZinxKernel::Zinx_Del_Proto(*_protocl);
		delete _protocl;
	}

}

AZinxHandler* GameChannel::GetInputNextStage(BytesMsg& _oInput)
{
	return _protocl;
}

ZinxTcpData* GameTcpFact::CreateTcpDataChannel(int _fd)
{
	auto pChannl = new GameChannel(_fd);
	ZinxKernel::Zinx_Add_Channel(*pChannl);
	auto pProtocol = new GameProtocl();
	ZinxKernel::Zinx_Add_Proto(*pProtocol);
	auto gameRole = new GameRole();
	pProtocol->_gameRole = gameRole;
	pProtocol->TcpChannel = pChannl;
	pChannl->_protocl = pProtocol;
	gameRole->_protocl = pProtocol;
	ZinxKernel::Zinx_Add_Role(*gameRole);

	return new GameChannel(_fd);
}
