#pragma once
#include <zinx.h>
#include "GameMsg.h"
#include "GameProtocol.h"
#include "GameChannel.h"
class GameRole : public Irole, public Player
{
	float x = 0;
	float y = 0;
	float z = 0;
	float v = 0;
	int iPid = 0;
	std::string szName;
	GameMsg* _createIDNameLogin();
public:
	GameRole();
	virtual ~GameRole();

	GameProtocl* _protocl = NULL;
	// ͨ�� Irole �̳�
	bool Init() override;

	UserData* ProcMsg(UserData& _poUserData) override;

	void Fini() override;


	// ͨ�� Player �̳�
	int GetX() override;

	int GetY() override;

};