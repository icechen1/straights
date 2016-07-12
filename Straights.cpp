#include "GameController.h"
#include "GameView.h"
#include <memory>
#include <iostream>
#include <gtkmm.h>

using namespace std;

std::shared_ptr<GameController> GameController::instance_; // WHYYY?

int runMainMenu(Glib::RefPtr<Gtk::Application> app, shared_ptr<GameView> gameView) {
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("mainmenu.glade");
	Gtk::Assistant *assistant;
	builder->get_widget("menu", assistant);
	assistant->signal_cancel().connect(sigc::mem_fun(*gameView, &GameView::handleQuit));
	assistant->signal_close().connect(sigc::mem_fun(*gameView, &GameView::handleQuit));
	//assistant->signal_apply().connect(sigc::mem_fun(*gameView, &GameView::startGame));

	for (int i = 0; i < 2; i++) {
		assistant->set_page_complete(*(assistant->get_nth_page(i)), true);
	}
	return app->run(*assistant);
}

// ensures: creates players and runs a full game of Straights
// returns: 0 if game properly runs
int main(int argc, char *argv[]) {
	int seed = 0;
	if (argc > 1) {
		seed = atoi(argv[1]); // load seed if provided in cmd
	}
	auto app =
		Gtk::Application::create(argc, argv,
			"org.straights");
	shared_ptr<GameView> gameView = shared_ptr<GameView>(new GameView(app));

	//Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("mainmenu.glade");
	//Gtk::Window *win;
	//builder->get_widget("menu", win);

	//Gtk::Button *button;
	//builder->get_widget("quit_btn", button);
	/*

	shared_ptr<GameController> controller = GameController::createInstance(seed, gameView);
	try {
		controller->playRound();
	}
	catch (Command c) {
		// quit game if quit command has been issued
		if (c.type_ == QUIT) {
			return code;
		}
	}
	*/
	// button->signal_clicked().connect(sigc::mem_fun(*gameView, &GameView::handleQuit));
	return runMainMenu(app, gameView);
}