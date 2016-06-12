#ifndef _PLAYER_
#define _PLAYER_
#include <vector>
#include "Card.h"
#include "Command.h"

enum PlayerType { HUMAN, COMPUTER };

class Player {
protected:
	int _id = -1;
	int _score = 0;
	std::vector<Card> discards;
	std::vector<Card> cards;
	std::vector<Card> getLegalMoves() const;
	Player(int id);
public:
	virtual PlayerType getPlayerType() const = 0;
	virtual Command play() = 0;
	int getPlayerId() const;
};

#endif