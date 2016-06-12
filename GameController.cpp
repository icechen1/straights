#include "GameController.h"
#include <memory>
using namespace std;

GameController::GameController(int seed) : state_(seed) {
}

std::shared_ptr<GameController> GameController::createInstance(int seed) {
	return shared_ptr<GameController>(new GameController(seed));
}

std::shared_ptr<GameController> GameController::getInstance() {
	return instance_;
}

GameState GameController::getState() const {
	return state_;
}

void GameController::playTurn(Command) {

}