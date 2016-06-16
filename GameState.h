#ifndef _GAMESTATE_
#define _GAMESTATE_
#include<vector>
#include<memory>
#include "Player.h"

struct GameState {
	std::vector<std::shared_ptr<Player>> players_;
	int seed_;

	GameState(int _seed) : seed_(_seed) {};
};

#endif
