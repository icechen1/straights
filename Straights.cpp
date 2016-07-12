#include "GameController.h"
#include "GameView.h"
#include <memory>
#include <iostream>
#include <gtkmm.h>

using namespace std;

std::shared_ptr<GameController> GameController::instance_; // WHYYY?

// ensures: creates players and runs a full game of Straights
// returns: 0 if game properly runs
int main(int argc, char *argv[]) {
	int seed = 0;
	if (argc > 1) {
		seed = atoi(argv[1]); // load seed if provided in cmd
	}
	auto app = Gtk::Application::create(argc, argv, "org.straights");
	shared_ptr<GameView> gameView = shared_ptr<GameView>(new GameView(app));
	//shared_ptr<GameController> controller = GameController::createInstance(seed, gameView);
	return gameView->run();
}