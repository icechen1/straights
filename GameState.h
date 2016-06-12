#ifndef _GAMESTATE_
#define _GAMESTATE_

#include "Player.h"
struct GameState {
	Player players[];
	Player currentPlayer;
	int seed;
};

#endif
