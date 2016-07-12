#ifndef _MENU_
#define _MENU_
#include <gtkmm.h>
#include "Subject.h"
#include "GameController.h"
#include "GameView.h"
class GameView;

class MainMenu {
private:
	Glib::RefPtr<Gtk::Application> app_;
	Gtk::Assistant *assistant_;
	Gtk::Switch* switches_[4];
	Gtk::Entry* entrySeed_;
	std::shared_ptr<GameView> view_;

	void startGame();
	void quit();
public:
	MainMenu(Glib::RefPtr<Gtk::Application> app, std::shared_ptr<GameView>);
	void run();
};
#endif