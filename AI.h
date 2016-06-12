#ifndef _AI_
#define _AI_
#include <vector>
#include "Player.h"

class AI : public Player {
public:
	PlayerType getPlayerType();
	void play();
};

#endif