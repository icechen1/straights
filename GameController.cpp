#include "GameController.h"
#include "GameView.h"

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
	state_ = shared_ptr<GameState>(new GameState(seed));
	state_->subscribe(view);
	// create the deck we're going to use for this game
	shared_ptr<Deck> t(new Deck(seed));
	state_->deck_ = t;
	// create a game record keeping stream
	record_ = unique_ptr<GameRecord>(new GameRecord());
}

void GameController::setPlayers(bool computers[]) {
	for (int i = 0; i < 4; i++) {
		shared_ptr<Player> player;
		if (!computers[i]) {
			shared_ptr<Player> player(new Human(i));
			state_->players_.push_back(player);
		}
		else {
			shared_ptr<Player> player(new AI(i));
			state_->players_.push_back(player);
		}
	}
}

// requires: a valid GameState objects in GameController
// modifies: Create a round, play the round and end the round
//			 Players score
// ensures: Players score are correctly updated
void GameController::playAITurns() {
	state_->currentRound_->playAITurns();
	if (state_->currentRound_->getRoundOver()) {
		endRound();
	}
}

bool GameController::playHumanCard(Card card) {
	shared_ptr<Player> player = getState()->currentRound_->getCurrentPlayer();
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
	if (player->verify(c)) {
		state_->currentRound_->playTurn(player, c);
		playAITurns();
		return true;
	}
	// invalid move
	return false;
}

// modifies: create a new round object and set it as currentRound_
void GameController::initStartRound() {
	state_->currentRound_ = shared_ptr<RoundController>(new RoundController());
	state_->notify();
}

// requires: a player has more than 80 points
void GameController::printWinner() const {
	int min = state_->players_[0]->getTotalScore();
	vector<shared_ptr<Player>> winningPlayers;
	for (shared_ptr<Player> p : state_->players_) {
		//find winner
		if (p->getTotalScore() < min) {
			winningPlayers.clear();
			winningPlayers.push_back(p);
			min = p->getTotalScore();
		} else if(p->getTotalScore() == min) {
			winningPlayers.push_back(p);
		}
	}

	// print out all winning players
	for (shared_ptr<Player> p : winningPlayers) {
		record_->printWinner(*p);
	}
}

// requires: all players played their cards
// modifies: clean all players' hand, played cards, discarded cards
//			 end the game or to play another round depending on the score
// ensures: player's score stay the same
void GameController::endRound() {
	// print post round information and clear hands
	for (shared_ptr<Player> p : state_->players_) {
		record_->printPostRound(*p);
		p->clearHand();
	}
	if (!isGameOver()) {
		// start another round
		initStartRound();
		playAITurns();
	}
	else {
		printWinner();
	}
}

// requires: player must be a human player
// modifies: the player at position i becomes an AI player
// ensures: played, discarded cards, cards in hand and scores stay the same
// return: a pointer to the new AI player
shared_ptr<Player> GameController::handleRageQuit(Player& player) {
	// (╯°□°)╯︵ ┻━┻
	int playerId = player.getPlayerId();
	shared_ptr<Player> ai(new AI(player));
	record_->printRageQuit(player);
	state_->players_.erase(state_->players_.begin() + playerId);
	state_->players_.insert(state_->players_.begin() + playerId, ai);
	return ai;
	// ┬──┬ ノ(゜-゜ノ)
}

// returns: a boolean to indicate if the game is over
bool GameController::isGameOver() {
	for (shared_ptr<Player> p : state_->players_) {
		if (p->getTotalScore() >= 80) {
			return true;
		}
	}
	return false;
}

// returns: a pointer to the GameController instance
shared_ptr<GameController> GameController::getInstance() {
	return instance_;
}

// returns: a pointer to the game state
shared_ptr<GameController::GameState> GameController::getState() const {
	return state_;
}

GameView* GameController::getView() const
{
	return view_;
}

GameRecord * GameController::getRecord() const
{
	return record_.get();
}

// returns: a pointer to the current game round
shared_ptr<RoundController> GameController::getCurrentRound() const {
	return state_->currentRound_;
}
