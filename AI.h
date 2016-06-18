#ifndef _AI_
#define _AI_
#include <vector>
#include "Player.h"

class AI : public Player {
public:
	PlayerType getPlayerType() const override; // returns COMPUTER
	Command play() override;  // play a move
	AI(int id) : Player(id) {} // constructs AI player with given ID
	AI(Player& other) : Player(other) {}; // copy constructor so AI can take over a human player over ragequit
};

#endif