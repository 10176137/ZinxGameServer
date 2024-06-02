#include "GameRole.h"
#include "GameMsg.h"
static AOIWorld world(0, 400, 0, 400, 20, 20);
GameMsg* GameRole::_createIDNameLogin()
{
	pb::SyncPid* pmsg = new pb::SyncPid();
	pmsg->set_pid(iPid);
	pmsg->set_username(szName);
	GameMsg* pRet = new GameMsg(GameMsg::MSG_TYPE_LOGIN_ID_NAME, pmsg);
	return pRet;
}
GameRole::GameRole()
{
	iPid = _protocl->TcpChannel->GetFd();
	szName = "tom";
}

GameRole::~GameRole()
{
}

bool GameRole::Init()
{
	bool bRet = false;
	bRet = world.AddPlayers(this);
	if (true == bRet)
	{
		ZinxKernel::Zinx_SendOut(*(_createIDNameLogin()), *_protocl);
	}

	return bRet;
}

UserData* GameRole::ProcMsg(UserData& _poUserData)
{
	MultMsg* _userData = dynamic_cast<MultMsg*>(&_poUserData);
	for (auto _foreach : _userData->GameMsgList)
	{
		std::cout << (int)_foreach->enMsgType << std::endl;
	}

	return NULL;
}

void GameRole::Fini()
{
}

int GameRole::GetX()
{
	return x;
}

int GameRole::GetY()
{
	return z;
}
