#include "GameController.h"
#include <memory>
#include <iostream>

using namespace std;

std::shared_ptr<GameController> GameController::instance_; // WHYYY?

// ensures: creates players and runs a full game of Straights
// returns: 0 if game properly runs
int main(int argc, char *argv[]) {
	int seed = 0;
	if (argc > 1) {
		seed = atoi(argv[1]); // load seed if provided in cmd
	}
	shared_ptr<GameController> controller = GameController::createInstance(seed);

	try {
		controller->playGame();
	}
	catch (Command c) {
		// quit game if quit command has been issued
		if (c.type_ == QUIT) {
			return 0;
		}
	}

	return 0;
}