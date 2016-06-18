#ifndef _ROUND_
#define _ROUND_

#include <vector>
#include <memory>
#include "Player.h"
#include "GameView.h"
#include "Deck.h"

class Round {
	bool firstTurn_ = true; // defaults to true - set to false after first turn
	std::shared_ptr<Player> currentPlayer_; // list of players in current round, in playing order
	std::vector<Card> playedCards_; // list of cards played by all players
	std::shared_ptr<GameState> gameState_; // pointer to the global game state
	void findStartingPlayer(); // finds player with 7S and mark as starting player
	void dealCards(); // deals 13 random cards to each player
public:
	Round(std::shared_ptr<GameState>); // initialized blank round with gamestate and deal cards
	void playRound(); // plays round to completion
	void handleTurn(); // handle a turn, call the associated player for move
	void playTurn(std::shared_ptr<Player>, Command); // performs the command the player chooses
	std::vector<Card> getPlayedCard() const; // returns list of played cards for round
};

#endif