#include "AOIWorld.h"
std::list<Player*> AOIWorld::GetSoundPlayers(Player* _player)
{
	std::list<Player*> ret;
	int grid_id = (_player->GetX() - x_Begin) / x_width + (_player->GetY() - y_Begin) / y_width * x_Count;
	int x_index = grid_id % x_Count;
	int y_index = grid_id / y_Count;
	if (x_index > 0 && y_index > 0)
	{
		std::list<Player*>& cur_list = _world[grid_id - 1 - x_Count].m_player;
		ret.insert(ret.begin(), cur_list.begin(),cur_list.end());
	}
	if (y_index > 0)
	{
		std::list<Player*>& cur_list = _world[grid_id - x_Count].m_player;
		ret.insert(ret.begin(), cur_list.begin(), cur_list.end());
	}
	if (x_index<x_Count-1 && y_index > 0)
	{
		std::list<Player*>& cur_list = _world[grid_id - x_Count + 1].m_player;
		ret.insert(ret.begin(), cur_list.begin(), cur_list.end());
	}
	if (x_index > 0 && y_index < y_Count-1)
	{
		std::list<Player*>& cur_list = _world[grid_id - 1 + x_Count].m_player;
		ret.insert(ret.begin(), cur_list.begin(), cur_list.end());
	}
	if (y_index < y_Count - 1)
	{
		std::list<Player*>& cur_list = _world[grid_id  + x_Count].m_player;
		ret.insert(ret.begin(), cur_list.begin(), cur_list.end());
	}
	if (x_index < x_Count - 1 && y_index < y_Count - 1)
	{
		std::list<Player*>& cur_list = _world[grid_id + x_Count + 1].m_player;
		ret.insert(ret.begin(), cur_list.begin(), cur_list.end());
	}
	if (x_index > 0)
	{
		std::list<Player*>& cur_list = _world[grid_id - 1].m_player;
		ret.insert(ret.begin(), cur_list.begin(), cur_list.end());
	}
	if (x_index < x_Count - 1)
	{
		std::list<Player*>& cur_list = _world[grid_id + 1].m_player;
		ret.insert(ret.begin(), cur_list.begin(), cur_list.end());
	}
	return ret;
}

bool AOIWorld::AddPlayers(Player* _player)
{
	// ¼ÆËãËùÊôÍø¸ñºÅ
	int grid_id = (_player->GetX() - x_Begin) / x_width + (_player->GetY() - y_Begin) / y_width * x_Count;
	_world[grid_id].m_player.push_back(_player);
	return true;
}

void AOIWorld::DelPlayer(Player* _player)
{
	int grid_id = (_player->GetX() - x_Begin) / x_width + (_player->GetY() - y_Begin) / y_width * x_Count;
	_world[grid_id].m_player.remove(_player);
}


AOIWorld::AOIWorld(int xBegin, int xEnd, int yBegin, int yEnd, int xCount, int yCount)
	:x_Begin(xBegin),y_Begin(yBegin),x_End(xEnd),y_End(yEnd),x_Count(xCount),y_Count(yCount)
{
	x_width = (x_End - x_Begin)/x_Count;
	y_width = (y_End - y_Begin) / y_Count;
	for (int i = 0; i<x_Count*y_Count;i++)
	{
		Grid temp;
		_world.push_back(temp);
	}
}

AOIWorld::~AOIWorld()
{
}
