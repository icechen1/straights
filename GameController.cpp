#include "GameController.h"
#include "GameView.h"

using namespace std;

GameController::GameController(int seed) : state_(seed) {
	for (int i = 1; i <= 4; i++) {
		// prompt to ask for player type
		PlayerType type = GameView::invitePlayer(i);
		shared_ptr<Player> player;
		if (type == HUMAN) {
			shared_ptr<Player> player(new Human(i));
			state_.players_.push_back(player);
		} else {
			shared_ptr<Player> player(new AI(i));
			state_.players_.push_back(player);
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

void GameController::playTurn(Command) {

}