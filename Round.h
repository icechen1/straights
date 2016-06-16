#ifndef _ROUND_
#define _ROUND_

#include <vector>
#include <memory>
#include "Player.h"
#include "GameView.h"
#include "Deck.h"

class Round {
	bool firstTurn_ = true;
	std::shared_ptr<Player> currentPlayer_;
	std::vector<Card> playedCards_;
	const std::shared_ptr<GameState> gameState_;
	void findStartingPlayer();
	void dealCards();
public:
	Round(const std::shared_ptr<GameState>);
	void playRound();
	void handleTurn();
	void playTurn(std::shared_ptr<Player>, Command);
	std::vector<Card> getPlayedCard() const;
};

#endif