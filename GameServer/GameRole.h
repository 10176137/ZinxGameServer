#pragma once
#include <zinx.h>
#include "GameProtocol.h"
class GameRole : public Irole, public Player
{
public:
	GameRole();
	virtual ~GameRole();

	GameProtocl* _protocl = NULL;
	// ͨ�� Irole �̳�
	bool Init() override;

	UserData* ProcMsg(UserData& _poUserData) override;

	void Fini() override;

};