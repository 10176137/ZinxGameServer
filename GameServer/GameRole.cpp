#include "GameRole.h"
#include "GameMsg.h"
static AOIWorld world(0, 400, 0, 400, 20, 20);
GameRole::GameRole()
{
}

GameRole::~GameRole()
{
}

bool GameRole::Init()
{
	bool bRet = false;
	bRet = world.AddPlayers(this);
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
