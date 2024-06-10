#include "GameRole.h"
#include "GameMsg.h"
static AOIWorld world(0, 400, 0, 400, 20, 20);

// 登录
GameMsg* GameRole::_createIDNameLogin()
{
	pb::SyncPid* pmsg = new pb::SyncPid();
	pmsg->set_pid(iPid);
	pmsg->set_username(szName);
	GameMsg* pRet = new GameMsg(GameMsg::MSG_TYPE_LOGIN_ID_NAME, pmsg);
	return pRet;
}

// 登出
GameMsg* GameRole::_createIDNameLoginOff()
{
	pb::SyncPid* pmsg = new pb::SyncPid();
	pmsg->set_pid(iPid);
	pmsg->set_username(szName);
	GameMsg* pRet = new GameMsg(GameMsg::MSG_TYPE_LOGOFF_ID_NAME, pmsg);
	return pRet;
}

// 获取周围玩家信息
GameMsg* GameRole::_createSrdPlays()
{
	pb::SyncPlayers* pMsg = new pb::SyncPlayers();
	auto soundPlays = world.GetSoundPlayers(this);
	for (auto single : soundPlays)
	{
		auto pPlays = pMsg->add_ps();

		// 父类指针转换子类对象
		auto pRole = dynamic_cast<GameRole*>(single);
		pPlays->set_pid(pRole->iPid);
		pPlays->set_username(pRole->szName);
		auto pPostion = pPlays->mutable_p();
		pPostion->set_x(pRole->x);
		pPostion->set_y(pRole->y);
		pPostion->set_z(pRole->z);
		pPostion->set_v(pRole->v);
	}
	
	GameMsg* pret = new GameMsg(GameMsg::MSG_TYPE_SRD_POSITION, pMsg);
	return pret;
}

// 创建自己信息
GameMsg* GameRole::_createSelfPostion()
{
	pb::BroadCast* pMsg = new pb::BroadCast();
	pMsg->set_pid(iPid);
	pMsg->set_username(szName);
	pMsg->set_tp(2); 
	auto pPosition = pMsg->mutable_p();
	pPosition->set_x(x);
	pPosition->set_y(y);
	pPosition->set_z(z);
	pPosition->set_v(v);
	GameMsg* pret = new GameMsg(GameMsg::MSG_TYPE_BROADCAST, pMsg);
	return pret;
}
GameRole::GameRole()
{
	szName = "tom";
	x = 100;
	y = 5;
	z = 100;
}

GameRole::~GameRole()
{
}

bool GameRole::Init()
{
	bool bRet = false;
	bRet = world.AddPlayers(this);
	iPid = _protocl->TcpChannel->GetFd();
	if (true == bRet)
	{
		ZinxKernel::Zinx_SendOut(*(_createIDNameLogin()), *_protocl);

		ZinxKernel::Zinx_SendOut(*(_createSrdPlays()), *_protocl);
		auto srd_list = world.GetSoundPlayers(this);
		for (auto single : srd_list)
		{
			auto pmsg = _createSelfPostion();
			auto Role = dynamic_cast<GameRole*>(single);
			ZinxKernel::Zinx_SendOut(*pmsg, *(Role->_protocl));
		}
	}

	return bRet;
}

UserData* GameRole::ProcMsg(UserData& _poUserData)
{
	MultMsg* _userData = dynamic_cast<MultMsg*>(&_poUserData);
	for (auto _foreach : _userData->GameMsgList)
	{
		std::cout << (int)_foreach->enMsgType << std::endl;
		std::cout << _foreach->pMsg->Utf8DebugString() << std::endl;
	}

	return NULL;
}

void GameRole::Fini()
{
	auto src_list = world.GetSoundPlayers(this);
	for (auto player : src_list)
	{
		auto Role = dynamic_cast<GameRole*>(player);
		auto pmsg = _createIDNameLoginOff();
		ZinxKernel::Zinx_SendOut(*pmsg, *(Role->_protocl));
	}
	world.DelPlayer(this);
}

int GameRole::GetX()
{
	return (int)x;
}

int GameRole::GetY()
{
	return (int)z;
}
