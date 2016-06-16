#include "GameController.h"
#include "GameView.h"
#include "Deck.h"

using namespace std;

shared_ptr<GameController> GameController::createInstance(int seed) {
	instance_ = shared_ptr<GameController>(new GameController(seed));
	return instance_;
}

GameController::GameController(int seed) : state_(seed), currentRound_(nullptr) {
	initPlayers();
	dealCards();
}

void GameController::initPlayers() {
	for (int i = 0; i < 4; i++) {
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
	deque<shared_ptr<Card>> cards = deck.getCards();
	for (shared_ptr<Player> p : state_.players_) {
		for (int i = 0; i < 13; i++) {
			p->dealCard(*cards.at(0));
			cards.pop_front();
		}
	}
}

void GameController::playGame() {
	initStartRound();
	currentRound_->playRound();
	endRound();
}

void GameController::initStartRound() {
	for (shared_ptr<Player> p : state_.players_) {
		for (Card c : p->getHand()) {
			if (c.getRank() == SEVEN && c.getSuit() == SPADE) {
				// this player starts
				currentRound_ = shared_ptr<Round>(new Round(p, state_));
				return;
			}
		}
	}
}

void GameController::endRound() {

	if (!isGameOver()) {
		cout << "new round" << endl;
		
		for (shared_ptr<Player> p : state_.players_) {
			p->clearHand();
		}

		dealCards();
		playGame();
	}
	else {
		cout << "gameover" << endl;
		for (;;) {

		}
	}
}

bool GameController::isGameOver() {
	for (shared_ptr<Player> p : state_.players_) {
		if (p->getTotalScore() >= 80) {
			return true;
		}
	}
	return false;
}

shared_ptr<GameController> GameController::getInstance() {
	return instance_;
}

GameState GameController::getState() const {
	return state_;
}

shared_ptr<Round> GameController::getCurrentRound() const {
	return currentRound_;
}
