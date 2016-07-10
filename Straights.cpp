#include "GameController.h"
#include <memory>
#include <iostream>
#include <gtkmm.h>

using namespace std;

std::shared_ptr<GameController> GameController::instance_; // WHYYY?

// ensures: creates players and runs a full game of Straights
// returns: 0 if game properly runs
//int main(int argc, char *argv[]) {
//	int seed = 0;
//	if (argc > 1) {
//		seed = atoi(argv[1]); // load seed if provided in cmd
//	}
//	shared_ptr<GameController> controller = GameController::createInstance(seed);
//
//	try {
//		controller->playRound();
//	}
//	catch (Command c) {
//		// quit game if quit command has been issued
//		if (c.type_ == QUIT) {
//			return 0;
//		}
//	}
//
//	return 0;
//}

int main(int argc, char *argv[])
{
	auto app =
		Gtk::Application::create(argc, argv,
			"org.gtkmm.examples.base");
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("screen.glade");
	Gtk::Window *win;
	builder->get_widget("window1", win);

	Gtk::Button *button;
	builder->get_widget("button1", button);
	return app->run(*win);
}