#ifndef _MENU_
#define _MENU_
#include <gtkmm.h>
#include "Subject.h"
#include "GameController.h"
#include "GameView.h"
class GameView;

class MainMenu {
private:
	Gtk::Assistant *assistant_;
	Gtk::Switch* switches_[4];
	Gtk::Entry* entrySeed_;
	GameView* view_;

	void startGame();
	void quit();
public:
	MainMenu(GameView*);
	void run();
};
#endif