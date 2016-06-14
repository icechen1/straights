#ifndef _AI_
#define _AI_
#include <vector>
#include "Player.h"

class AI : public Player {
public:
	PlayerType getPlayerType() const override;
	Command play() override;
	Command play(const Command) const override;
	AI(int id) : Player(id) {};
};

#endif