#ifndef _HUMAN_
#define _HUMAN_
#include <vector>
#include "Player.h"

class Human : public Player {
public:
	PlayerType getPlayerType() const override;
	Command play() override;
	Command playFirstTurn() override;
	Human(int id) : Player(id) {};
};

#endif