#ifndef _ROUND_
#define _ROUND_

#include <vector>
#include <memory>
#include "Player.h"
#include "GameView.h"

class Round {
	bool firstTurn_;
	std::shared_ptr<Player> currentPlayer_;
	std::vector<Card> playedCards_;
	const GameState& gameState_;

public:
	Round(std::shared_ptr<Player>, GameState& const);
	void playRound();
	void firstTurn();
	void handleTurn();
	void playTurn(std::shared_ptr<Player>, Command);
	std::vector<Card> getPlayedCard() const;
};

#endif