#include "GameController.h"
#include <memory>
#include <iostream>

using namespace std;

std::shared_ptr<GameController> GameController::instance_; // WHYYY?

int main(int argc, char *argv[]) {
	int seed = 0;
	if (argc > 1) {
		seed = atoi(argv[1]);
	}
	shared_ptr<GameController> controller = GameController::createInstance(seed);

	try {
		controller->playGame();
	}
	catch (Command c) {
		if (c.type_ == QUIT) {
			return 0;
		}
	}

	return 0;
}