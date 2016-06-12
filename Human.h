#ifndef _HUMAN_
#define _HUMAN_
#include <vector>
#include "Player.h"

class Human : public Player {
public:
	PlayerType getPlayerType();
	void play();
};

#endif