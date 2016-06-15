#include "GameController.h"
#include "GameView.h"
#include "Deck.h"

using namespace std;

GameController::GameController(int seed) : state_(seed) {
	initPlayers();
	dealCards();
	initStartRound();
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

void GameController::newRound() {
	for (shared_ptr<Player> p : state_.players_) {
		p->nextRound();
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

void GameController::initStartRound() {
	state_.playedCards_.clear();
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
	// check if we have reached end condition
	shared_ptr<Player> p = state_.currentPlayer_;
	if (p->getPlayerType() == COMPUTER) {
		playTurn(p, p->play());
	}
	else {
		// human
		Command c = GameView::startHumanTurn(*(state_.currentPlayer_));
		playTurn(p, c);
	}
}

void GameController::startRound() {
	shared_ptr<Player> p = state_.currentPlayer_;
	GameView::startRound(p->getPlayerId());
	if (p->getPlayerType() == COMPUTER) {
		Command c = Command();
		c.type_ = PLAY;
		c.card_ = Card(SPADE, SEVEN);
		p->play(c);
		playTurn(p, c);
		return;
	}
	handleTurn();
}


void GameController::playTurn(shared_ptr<Player> player, Command command) {
	// handle play
	// TODO input check
	switch (command.type_) {
	case PLAY:
		player->playCard(command.card_);
		state_.playedCards_.push_back(command.card_);
		break;
	case DISCARD:
		player->discardCard(command.card_);
		break;
	}

	// handle discard

	// handle end condition
	if (player->getHand().size() == 0) {
		cout << "new round" << endl;
		newRound();
		if (!isGameOver()) {
			dealCards();
			initStartRound();
		} else {
			cout << "gameover" << endl;
			for (;;) {

			}
		}

	}
	// increment current player
	int newPosition = (state_.currentPlayer_->getPlayerId() + 1) % 4;
	state_.currentPlayer_ = state_.players_.at(newPosition);
}