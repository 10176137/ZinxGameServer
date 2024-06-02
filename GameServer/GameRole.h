#pragma once
#include <zinx.h>
#include "GameProtocol.h"
class GameRole : public Irole, public Player
{
public:
	GameRole();
	virtual ~GameRole();

	GameProtocl* _protocl = NULL;
	// Í¨¹ý Irole ¼Ì³Ð
	bool Init() override;

	UserData* ProcMsg(UserData& _poUserData) override;

	void Fini() override;

};