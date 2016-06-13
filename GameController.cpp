#include "GameController.h"
#include "GameView.h"
#include "Deck.h"

using namespace std;

GameController::GameController(int seed) : state_(seed) {
	initPlayers();
	dealCards();
	initStartTurn();
}

void GameController::initPlayers() {
	for (int i = 1; i <= 4; i++) {
		// prompt to ask for player type
		PlayerType type = GameView::invitePlayer(i);
		shared_ptr<Player> player;
		if (type == HUMAN) {
			shared_ptr<Player> player(new Human(i));
			state_.players_.push_back(player);
		}
		else {
			shared_ptr<Player> player(new AI(i));
			state_.players_.push_back(player);
		}
	}
}

void GameController::dealCards() {
	Deck deck = Deck(state_.seed_);
	deck.shuffle();
	deque<Card> cards = deck.getCards();
	for (shared_ptr<Player> p : state_.players_) {
		for (int i = 0; i < 13; i++) {
			p->dealCard(cards.at(0));
			cards.pop_front();
		}
	}
}

void GameController::initStartTurn() {
	for (shared_ptr<Player> p : state_.players_) {
		for (Card c : p->getHand()) {
			if (c.getRank() == SEVEN && c.getSuit() == SPADE) {
				// this player starts
				state_.currentPlayer_ = p;
				return;
			}
		}
	}
}

shared_ptr<GameController> GameController::createInstance(int seed) {
	instance_ = shared_ptr<GameController>(new GameController(seed));
	return instance_;
}

shared_ptr<GameController> GameController::getInstance() {
	return instance_;
}

GameState GameController::getState() const {
	return state_;
}

void GameController::handleTurn() {
	shared_ptr<Player> p = state_.currentPlayer_;
	GameView::startRound(p->getPlayerId());
	if (p->getPlayerType() == COMPUTER) {

	}
	else {
		// human
		Command c = GameView::startHumanTurn(*(state_.currentPlayer_));
		p->play();
		playTurn(c);
	}
}

void GameController::playTurn(Command) {

}