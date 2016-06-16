#include "Round.h"

using namespace std;

Round::Round(const GameState& _state) : gameState_(_state) {
	dealCards();
	findStartingPlayer();
}

void Round::findStartingPlayer() {
	for (shared_ptr<Player> p : gameState_.players_) {
		for (Card c : p->getHand()) {
			if (c.getRank() == SEVEN && c.getSuit() == SPADE) {
				// this player starts
				currentPlayer_ = p;
				return;
			}
		}
	}
}

void Round::dealCards() {
	gameState_.deck_->shuffle();
	deque<shared_ptr<Card>> cards = gameState_.deck_->getCards();
	for (shared_ptr<Player> p : gameState_.players_) {
		for (int i = 0; i < 13; i++) {
			p->dealCard(*cards.at(0));
			cards.pop_front();
		}
	}
}

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
	case DECK:
		GameView::printDeck(*(gameState_.deck_));
		break;
	case RAGEQUIT:
	case QUIT:
	case BAD_COMMAND:
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