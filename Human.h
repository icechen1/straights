#ifndef _HUMAN_
#define _HUMAN_
#include <vector>
#include <algorithm>
#include "Player.h"

class Human : public Player {
public:
	PlayerType getPlayerType() const override; // returns HUMAN
	Command play() override; // play a move
	Human(int id) : Player(id) {}; // constructs Human player with given ID
};

#endif