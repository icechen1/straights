#include "RoundController.h"
#include "GameController.h"

using namespace std;

// ensures: set initial random dealt cards and starting player
// returns: a constructed Round object
RoundController::RoundController() {
	vector<Card> cards;
	GameState::getInstance()->setPlayedCards(cards);
	GameState::getInstance()->setFirstTurn(true);
	dealCards();
	findStartingPlayer();
}

// requires: gameState_ is not empty, and has players
// modifies: sets the currentPlayer_ to the player with a 7S
// ensures: does not modify the players
void RoundController::findStartingPlayer() {
	shared_ptr<GameState> state = GameState::getInstance();

	vector<shared_ptr<Player>> players = state->getPlayers();
	for (shared_ptr<Player> p : players) {
		for (Card c : p->getHand()) {
			if (c.getRank() == SEVEN && c.getSuit() == SPADE) {
				// this player starts
				state->setCurrentPlayer(p);
				return;
			}
		}
	}
}

// requires: gameState_ is not empty, and has players
// requires: there are cards in the deck
// modifies: deals 13 random cards to each player (class field)
// ensures: does not modify the game state
void RoundController::dealCards() {
	shared_ptr<GameController> instance = GameController::getInstance();
	shared_ptr<GameState> state = GameState::getInstance();

	state->getDeck()->shuffle();
	deque<shared_ptr<Card>> cards = state->getDeck()->getCards();
	for (shared_ptr<Player> p : state->getPlayers()) {
		for (int i = 0; i < 13; i++) {
			p->dealCard(*cards.at(0));
			cards.pop_front();
		}
	}
}

// requires: valid player and command
// modifies: list of legal moves
// ensures: player.play() gets called
void RoundController::handleTurn() {
	shared_ptr<Player> p = GameState::getInstance()->getCurrentPlayer();
	// ask the player to make a move
	Command c = p->play();
	// play move
	playTurn(p, c);
}

// requires: valid player
// modifies: state about current round
// ensures: a full round is played after the function runs
void RoundController::playAITurn() {
	if (GameState::getInstance()->getCurrentPlayer()->getHand().size() > 0
		&& GameState::getInstance()->getCurrentPlayer()->getPlayerType() == COMPUTER) {
		handleTurn();
	}
	return;
}

// requires: valid player and command
// modifies: plays the action, modifies the player and the Round with the action taken, may end the round
// ensures: the next player will become the current player
void RoundController::playTurn(shared_ptr<Player> player, Command command) {
	shared_ptr<GameController> instance = GameController::getInstance();
	shared_ptr<GameState> state = GameState::getInstance();
	vector<Card> playedlist = state->getPlayedCards();

	// handle play
	switch (command.type_) {
	case PLAY:
		player->playCard(command.card_);
		instance->getRecord()->printPlayTurn(*player, command);
		playedlist.push_back(command.card_);
		state->setPlayedCards(playedlist);
		break;
	case DISCARD:
		player->discardCard(command.card_);
		instance->getRecord()->printDiscardTurn(*player, command);
		break;
	case RAGEQUIT:
		state->setCurrentPlayer(GameController::getInstance()->handleRageQuit(*player));
		handleTurn();	//Let the PC to play the turn instead of continuing the turn by human
		return;
	case DECK:
	case QUIT:
	case BAD_COMMAND:
		break;
	}

	// increment current player
	state->setFirstTurn(false);

	int newPosition = (state->getCurrentPlayer()->getPlayerId() + 1) % 4;
	state->setCurrentPlayer(state->getPlayers().at(newPosition));

	// update
	state->notify();
}