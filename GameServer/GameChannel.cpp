#include "GameChannel.h"

GameChannel::GameChannel(int _fd):ZinxTcpData(_fd)
{
}

GameChannel::~GameChannel()
{
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
	pProtocol->TcpChannel = pChannl;
	pChannl->_protocl = pProtocol;
	return new GameChannel(_fd);
}
