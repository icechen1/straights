#include "GameController.h"
#include "GameView.h"
#include <memory>
#include <iostream>
#include <gtkmm.h>

using namespace std;

std::shared_ptr<GameController> GameController::instance_; // WHYYY?
std::shared_ptr<GameState> GameState::instance_; // WHYYY?

// ensures: creates players and runs a full game of Straights
// returns: 0 if game properly runs
int main(int argc, char *argv[]) {
	auto app = Gtk::Application::create(argc, argv, "org.straights");
	GameView gameView;
	return gameView.run(app);
}

// bonus ideas:
// leaderboard
// textbox with player actions
// achievements
