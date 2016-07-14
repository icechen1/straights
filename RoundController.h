#ifndef _ROUNDCONTROLLER_
#define _ROUNDCONTROLLER_

#include <vector>
#include <memory>
#include "Player.h"
#include "GameView.h"
#include "Deck.h"

class RoundController {
	bool roundOver_ = false;
	bool firstTurn_ = true; // defaults to true - set to false after first turn
	std::shared_ptr<Player> currentPlayer_; // list of players in current round, in playing order
	std::vector<Card> playedCards_; // list of cards played by all players

	void findStartingPlayer(); // finds player with 7S and mark as starting player
	void dealCards(); // deals 13 random cards to each player
public:
	RoundController(); // initialized blank round and deal cards
	void playAITurns(); // plays AI turns during the round until game ends or a human turn
	void handleTurn(); // handle a turn, call the associated player for move
	void playTurn(std::shared_ptr<Player>, Command); // performs the command the player chooses
	std::shared_ptr<Player> getCurrentPlayer() const;
	bool getRoundOver() const;
	bool getFirstTurn() const;
	std::vector<Card> getPlayedCard() const; // returns list of played cards for round
};

#endif