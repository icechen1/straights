#include "Round.h"

using namespace std;

Round::Round(std::shared_ptr<Player> _p, GameState& const _state) : 
	currentPlayer_(_p), gameState_(_state), firstTurn_(true) {}

void Round::handleTurn() {
	// check if we have reached end condition
	shared_ptr<Player> p = currentPlayer_;

	if (firstTurn_ == true) {
		firstTurn();
	}
	else {
		Command c;
		if (p->getPlayerType() == COMPUTER) {
			c = p->play();
		}
		else {
			// human
			c = GameView::startHumanTurn(*(currentPlayer_));
		}
		playTurn(p, c);
	}
}

void Round::playRound() {
	while (currentPlayer_->getHand().size() != 0){
		handleTurn();
	}
	return;
}

void Round::firstTurn() {
	shared_ptr<Player> p = currentPlayer_;
	GameView::startRound(p->getPlayerId());

	playTurn(p, p->playFirstTurn());

	firstTurn_ = false;
}


void Round::playTurn(shared_ptr<Player> player, Command command) {
	// handle play
	// TODO input check
	switch (command.type_) {
	case PLAY:
		player->playCard(command.card_);
		GameView::printPlayTurn(*player, command);
		playedCards_.push_back(command.card_);
		break;
	case DISCARD:
		player->discardCard(command.card_);
		GameView::printDiscardTurn(*player, command);
		break;
	}

	// handle discard

	// increment current player
	int newPosition = (currentPlayer_->getPlayerId() + 1) % 4;
	currentPlayer_ = gameState_.players_.at(newPosition);
}

vector<Card> Round::getPlayedCard() const {
	return playedCards_;
}