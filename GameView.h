#ifndef _GAMEVIEW_
#define _GAMEVIEW_

#include <iostream>
#include "Command.h"
#include "Player.h"
#include "GameState.h"

class GameView {
public:
	char invitePlayer(int);
	void startRound(int);
	Command startTurn(Player, GameState);
};

#endif