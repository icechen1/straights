#include "GameController.h"
#include <memory>

using namespace std;

std::shared_ptr<GameController> GameController::instance_; // WHYYY?

int main(int argc, char *argv[]) {
	int seed = 0;
	if (argc > 0) {
		seed = atoi(argv[0]);
	}
	shared_ptr<GameController> controller = GameController::createInstance(seed);


	return 0;
}