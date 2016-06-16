#ifndef _HUMAN_
#define _HUMAN_
#include <vector>
#include <algorithm>
#include "Player.h"

class Human : public Player {
public:
	PlayerType getPlayerType() const override;
	Command play() override;
	Human(int id) : Player(id) {};
};

#endif