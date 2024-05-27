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

	// ����Э�����
	virtual AZinxHandler* GetInputNextStage(BytesMsg& _oInput) override;
};

class GameTcpFact :public IZinxTcpConnFact
{
public:

	// ͨ�� IZinxTcpConnFact �̳�
	ZinxTcpData* CreateTcpDataChannel(int _fd) override;

};