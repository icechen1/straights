#ifndef _MENU_
#define _MENU_
#include <gtkmm.h>
#include "Subject.h"
#include "GameController.h"
#include "GameView.h"
class GameView;

// the main menu is the window the user must use to create a new game
class MainMenu {
private:
	// references to gui elements
	Gtk::Assistant *assistant_;
	Gtk::Switch* switches_[4];
	Gtk::Entry* entrySeed_;

	// reference to the main game menu
	GameView* view_;

	void startGame(); // handler when the apply button is pressed
	void quit(); // handler for quitting the new game menu
public:
	MainMenu(GameView*); // constructor for main menu using glade layout and grabs relevant refeces
	void run(); // runs (shows) the menu
};
#endif