#ifndef _PLAYER_
#define _PLAYER_
#include <vector>
#include "Card.h"
#include "Command.h"

enum PlayerType { HUMAN, COMPUTER };

class Player {
protected:
	int total_score_ = 0;
	std::vector<Card> discards_;
	std::vector<Card> cards_;
	std::vector<Card> legalMoves_;
	int id_ = -1;
	Player(int id);
	Player(Player&); // copy constructor
public:
	virtual PlayerType getPlayerType() const = 0;
	virtual Command play() = 0;
	int getPlayerId() const;
	void clearHand();
	std::vector<Card> getDiscards() const;
	int getRoundScore() const;
	int getTotalScore() const;

	void dealCard(Card c);

	void computeLegalMoves(bool);
	std::vector<Card> getLegalMoves() const;
	std::vector<Card> getHand() const;

	void playCard(Card);
	void discardCard(Card);
};

#endif