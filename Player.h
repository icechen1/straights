#ifndef _PLAYER_
#define _PLAYER_
#include <vector>
#include "Card.h"
#include "Command.h"

enum PlayerType { HUMAN, COMPUTER };

class Player {
protected:
	int total_score_ = 0; // total score for all rounds for given player
	std::vector<Card> discards_; // list of discards for the player in the current round
	std::vector<Card> cards_; // list of cards on hand for the player in the current round
	int id_ = -1; // player id in the range from 0 to 3
	Player(int id); // constructs player with assigned id
	Player(Player&); // copy constructor
public:
	virtual PlayerType getPlayerType() const = 0; // abstract function - returns the type of player by derived classes
	virtual Command play() = 0; // abstract function - derived classes will implement player logic
	int getPlayerId() const; // returns the player id
	void clearHand(); // clears discards and list of cards on hand
	std::vector<Card> getDiscards() const; // returns list of discards
	int getRoundScore() const; // computes current round score
	int getTotalScore() const; // returns total score
	void dealCard(Card c); // adds a card c to current hand
	std::vector<Card> getLegalMoves() const; // returns list of legal moves for the turn
	std::vector<Card> getHand() const; // returns list of cards on hand
	void playCard(Card); // removes card from list of cards
	void discardCard(Card); // removes card from list of cards, adds to discards and round score
	bool verify(Command c); // verify a move
};

#endif