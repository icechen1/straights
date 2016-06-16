#ifndef _PLAYER_
#define _PLAYER_
#include <vector>
#include "Card.h"
#include "Command.h"

enum PlayerType { HUMAN, COMPUTER };

class Player {
protected:
	int round_score_ = 0;
	int total_score_ = 0;
	std::vector<Card> discards_;
	std::vector<Card> cards_;
	int id_ = -1;
	Player(int id);
public:
	virtual PlayerType getPlayerType() const = 0;
	virtual Command play() = 0;
	virtual Command playFirstTurn() = 0;
	int getPlayerId() const;
	void clearHand();
	std::vector<Card> getDiscards() const;
	int getRoundScore() const;
	int getTotalScore() const;

	void dealCard(Card c);

	std::vector<Card> getLegalMoves() const;
	std::vector<Card> getHand() const;

	void playCard(Card);
	void discardCard(Card);
};

#endif