#pragma once
#include <list>
#include <vector>
class Player
{
public:
	virtual int GetX() = 0;
	virtual int GetY() = 0;

};

class Grid 
{
public:
	std::list<Player*> m_player;
};

class AOIWorld
{
	int x_Begin = 0;
	int x_End = 0;
	int y_Begin = 0;
	int y_End = 0;
	int x_Count = 0;
	int y_Count = 0;
	int x_width = 0;
	int y_width = 0;
	std::vector<Grid> _world;

public:

	// 获取周围玩家位值
	std::list<Player*>GetSoundPlayers(Player* _player);

	bool AddPlayers(Player* _player);
	void DelPlayer(Player* _player);
	AOIWorld(int xBegin,
	int xEnd = 0,
	int yBegin ,
	int yEnd ,
	int xCount,
	int yCount);
	~AOIWorld();
};
