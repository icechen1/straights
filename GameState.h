#ifndef _GAMESTATE_
#define _GAMESTATE_
#include<vector>
#include<memory>
#include "Player.h"

struct GameState {
	std::vector<std::shared_ptr<Player>> players;
	std::shared_ptr<Player> currentPlayer;
	std::vector<Card> playedCards;
	int seed;

	GameState(int seed) : seed(seed) {};
};

#endif
