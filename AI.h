#ifndef _AI_
#define _AI_
#include <vector>
#include "Player.h"

class AI : public Player {
public:
	PlayerType getPlayerType() const override;
	Command play() override;
	AI(int id) : Player(id) {};
	AI(Player& other) : Player(other) {};
};

#endif