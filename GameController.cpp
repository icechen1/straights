﻿#include "GameController.h"

using namespace std;

//returns: a pointer to an instance of GameController
shared_ptr<GameController> GameController::createInstance(int seed, bool computers[], GameView* view) {
	instance_ = shared_ptr<GameController>(new GameController(seed, view));
	instance_->setPlayers(computers);
	return instance_;
}

// modifies: create a new GameState
//			 initialize a new deck
//			 initialize 4 players
// returns:	A game controller object to be used for the full game
GameController::GameController(int seed, GameView* view) : view_(view) {
	// create game state
	shared_ptr<GameState> old_state = GameState::getInstance();
	shared_ptr<GameState> state = GameState::createInstance(seed);
	state->subscribe(view);
	// create the deck we're going to use for this game
	if (old_state == nullptr) {
		// new game
		shared_ptr<Deck> t(new Deck(seed));
		state->setDeck(t);
	}
	else if (old_state->getSeed() != seed) {
		// do not reuse deck as seed has changed
		shared_ptr<Deck> t(new Deck(seed));
		state->setDeck(t);
	}
	else {
		// reuse deck
		state->setDeck(old_state->getDeck());
	}

	// create a game record keeping stream
	record_ = unique_ptr<GameRecord>(new GameRecord());
}

// requires: array of boolean of size 4, true-> computer/false->human
// modifies: players in the game state
// ensures: game state now have 4 players (human or AI depending on the array)
void GameController::setPlayers(bool computers[]) {
	shared_ptr<GameState> state = GameState::getInstance();
	vector<shared_ptr<Player>> playerList;
	for (int i = 0; i < 4; i++) {
		shared_ptr<Player> player;
		if (!computers[i]) {
			shared_ptr<Player> player(new Human(i));
			playerList.push_back(player);
		}
		else {
			shared_ptr<Player> player(new AI(i));
			playerList.push_back(player);
		}
	}
	state->setPlayers(playerList);
}

// requires: Game must be initialized
// modifies: Game State
// ensures: Make AI to play the turn if needed and/or end the game
void GameController::playTurn() {
	shared_ptr<GameState> state = GameState::getInstance();
	if (state->getCurrentPlayer()->getPlayerType() == COMPUTER) {
		roundController_->playAITurn();
	}
	if (state->isRoundEnd() == true) {
		endRound();
	}
}

// requires: A Card on the player hand that is to be played
// modifies: Game State
// ensures: Plays a human turn with the provided card (can be either discard or play)
// returns: true or false depending if the provided Card is a valid play
bool GameController::playHumanTurn(Card card) {
	shared_ptr<GameState> state = GameState::getInstance();

	shared_ptr<Player> player = state->getCurrentPlayer();
	vector<Card> hand = player->getHand();
	vector<Card> validMoves = player->getLegalMoves();

	Command c;

	if (std::find(validMoves.begin(), validMoves.end(), card) != validMoves.end()) {
		c.type_ = PLAY;
		c.card_ = card;
	}
	else {
		c.type_ = DISCARD;
		c.card_ = card;
	}
	//verify
	if (player->verify(c) == true) {
		roundController_->playTurn(player, c);
		return true;
	}
	// invalid move
	return false;
}

// modifies: create a new round object and set it as currentRound_
void GameController::initStartRound() {
	roundController_ = unique_ptr<RoundController>(new RoundController());
	// print round start message
	record_->startRound(*(GameState::getInstance()->getCurrentPlayer()));
	view_->initGameRoundWatcher();
}

// requires: a player has more than 80 points
void GameController::printWinner() const {
	shared_ptr<GameState> state = GameState::getInstance();
	vector<shared_ptr<Player>> winningPlayers = state->computeWinners();

	// print out all winning players
	for (shared_ptr<Player> p : winningPlayers) {
		record_->printWinner(*p);
	}
}

// requires: all players played their cards
// modifies: clean all players' hand, played cards, discarded cards
//			 end the game or to play another round depending on the score
//			 calculate new scores
void GameController::endRound() {
	shared_ptr<GameState> state = GameState::getInstance();
	view_->disconnectWatcher();
	state->computeTotalScore();

	bool gameOver = state->isGameOver();
	view_->showRoundEndDialog(gameOver);

	// clear players hand
	for (shared_ptr<Player> p : state->getPlayers()) {
		record_->printPostRound(*p);
		p->clearHand();
	}

	if (gameOver) {
		printWinner();
	}
	state->notify();

	if (!gameOver) {
		// start another round
		initStartRound();
	}
}

// requires: player must be a human player
// modifies: the player at position i becomes an AI player
// ensures: played, discarded cards, cards in hand and scores stay the same
// return: a pointer to the new AI player
shared_ptr<Player> GameController::handleRageQuit(Player& player) {
	// (╯°□°)╯︵ ┻━┻
	shared_ptr<GameState> state = GameState::getInstance();

	int playerId = player.getPlayerId();
	shared_ptr<Player> ai(new AI(player));
	record_->printRageQuit(player);
	vector<shared_ptr<Player>> players = state->getPlayers();
	players.erase(players.begin() + playerId);
	players.insert(players.begin() + playerId, ai);
	state->setPlayers(players);
	return ai;
	// ┬──┬ ノ(゜-゜ノ)
}

// returns: a pointer to the GameController instance
shared_ptr<GameController> GameController::getInstance() {
	return instance_;
}

// returns: a pointer to the game state
shared_ptr<GameState> GameController::getState() const {
	return GameState::getInstance();
}

// returns: a pointer to the main game view
GameView* GameController::getView() const
{
	return view_;
}

// returns: a pointer to the record of current game
GameRecord * GameController::getRecord() const
{
	return record_.get();
}

// returns: a pointer to the current game round controller
RoundController* GameController::getCurrentRound() const {
	return roundController_.get();
}
