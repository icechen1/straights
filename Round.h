#ifndef _ROUND_
#define _ROUND_

#include <vector>
#include <memory>
#include "Player.h"
#include "GameView.h"
#include "Deck.h"

class Round {
	bool roundOver_ = false;
	bool firstTurn_ = true; // defaults to true - set to false after first turn
	std::shared_ptr<Player> currentPlayer_; // list of players in current round, in playing order
	std::vector<Card> playedCards_; // list of cards played by all players

	void findStartingPlayer(); // finds player with 7S and mark as starting player
	void dealCards(); // deals 13 random cards to each player
public:
	Round(); // initialized blank round and deal cards
	void playRound(); // plays round to completion
	void handleTurn(); // handle a turn, call the associated player for move
	void playTurn(std::shared_ptr<Player>, Command); // performs the command the player chooses
	std::shared_ptr<Player> getCurrentPlayer() const;
	bool getRoundOver() const;
	std::vector<Card> getPlayedCard() const; // returns list of played cards for round
};

#endif