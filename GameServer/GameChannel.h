#pragma once
#include <ZinxTCP.h>
#include "GameProtocol.h"
class GameChannel :public ZinxTcpData 
{
private:
public:
	GameProtocl* _protocl = NULL;
	GameChannel(int _fd);
	virtual ~GameChannel();

	// 返回协议对象
	virtual AZinxHandler* GetInputNextStage(BytesMsg& _oInput) override;
};

class GameTcpFact :public IZinxTcpConnFact
{
public:

	// 通过 IZinxTcpConnFact 继承
	ZinxTcpData* CreateTcpDataChannel(int _fd) override;

};