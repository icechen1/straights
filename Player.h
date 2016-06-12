#ifndef _PLAYER_
#define _PLAYER_
#include<vector>
#include "Card.h"

enum PlayerType { HUMAN, COMPUTER };

class Player {
	int score = 0;
	std::vector<Card> discards;
	std::vector<Card> cards;
	std::vector<Card> getLegalMoves() const;
public:
	virtual PlayerType getPlayerType() = 0;
	virtual void play() = 0;
};

#endif