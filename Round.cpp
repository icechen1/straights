#include "Round.h"
#include "GameController.h"

using namespace std;

// ensures: set initial random dealt cards and starting player
// returns: a constructed Round object
Round::Round(shared_ptr<GameState> _state) : gameState_(_state) {
	dealCards();
	findStartingPlayer();
}

// requires: gameState_ is not empty, and has players
// modifies: sets the currentPlayer_ to the player with a 7S
// ensures: does not modify the players
void Round::findStartingPlayer() {
	for (shared_ptr<Player> p : gameState_->players_) {
		for (Card c : p->getHand()) {
			if (c.getRank() == SEVEN && c.getSuit() == SPADE) {
				// this player starts
				currentPlayer_ = p;
				return;
			}
		}
	}
}

// requires: gameState_ is not empty, and has players
// requires: there are cards in the deck
// modifies: deals 13 random cards to each player (class field)
// ensures: does not modify the game state
void Round::dealCards() {
	gameState_->deck_->shuffle();
	deque<shared_ptr<Card>> cards = gameState_->deck_->getCards();
	for (shared_ptr<Player> p : gameState_->players_) {
		for (int i = 0; i < 13; i++) {
			p->dealCard(*cards.at(0));
			cards.pop_front();
		}
	}
}

// requires: valid player and command
// modifies: list of legal moves
// ensures: player.play() gets called
void Round::handleTurn() {
	shared_ptr<Player> p = currentPlayer_;
	// compute the list of legal moves
	p->computeLegalMoves(firstTurn_);
	// ask the player to make a move
	Command c = p->play();
	// play move
	playTurn(p, c);
}

// requires: valid player
// modifies: state about current round
// ensures: a full round is played after the function runs
void Round::playRound() {
	// print round start message
	GameView::startRound(currentPlayer_->getPlayerId() + 1);
	// play turns until a player runs out of cards
	while (currentPlayer_->getHand().size() != 0) {
		handleTurn();
	}
	return;
}

// requires: valid player and command
// modifies: plays the action, modifies the player and the Round with the action taken, may end the round
// ensures: the next player will become the current player
void Round::playTurn(shared_ptr<Player> player, Command command) {
	// handle play
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
	case RAGEQUIT:
		currentPlayer_ = GameController::getInstance()->handleRageQuit(*player);
		handleTurn();	//Let the PC to play the turn instead of continuing the turn by human
		return;
	case DECK:
	case QUIT:
	case BAD_COMMAND:
		break;
	}

	// handle discard

	// increment current player
	firstTurn_ = false;

	int newPosition = (currentPlayer_->getPlayerId() + 1) % 4;
	currentPlayer_ = gameState_->players_.at(newPosition);
}

// requires: a list of played cards
// ensures: nothing is modified
// returns: list of cards that have been played this round
vector<Card> Round::getPlayedCard() const {
	return playedCards_;
}