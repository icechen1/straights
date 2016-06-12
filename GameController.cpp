#include "GameController.h"
#include <memory>
using namespace std;

GameController::GameController(int seed) : state(seed) {
}

std::shared_ptr<GameController> GameController::createInstance(int seed) {
	return shared_ptr<GameController>(new GameController(seed));
}

std::shared_ptr<GameController> GameController::getInstance() {
	return instance;
}

GameState GameController::getState() const {

}

void GameController::playTurn(Command) {

}