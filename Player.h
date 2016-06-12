#ifndef _PLAYER_
#define _PLAYER_
#include <vector>
#include "Card.h"

enum PlayerType { HUMAN, COMPUTER };

class Player {
protected:
	int score_ = 0;
	std::vector<Card> discards_;
	std::vector<Card> cards_;
public:
	virtual PlayerType getPlayerType() = 0;
	virtual void play() = 0;

	std::vector<Card> getLegalMoves() const;
	std::vector<Card> getHand() const;
};

#endif