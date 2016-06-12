#ifndef _AI_
#define _AI_
#include <vector>
#include "Player.h"

class AI : public Player {
public:
	PlayerType getPlayerType();
	Command play();
	AI(int id) : Player(id) {};
};

#endif