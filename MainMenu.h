#ifndef _MENU_
#define _MENU_
#include <gtkmm.h>

class MainMenu {
private:
	Glib::RefPtr<Gtk::Application> app_;
	Gtk::Assistant *assistant_;
	Gtk::Switch* switches_[4];

	void startGame();
	void quit();
public:
	MainMenu(Glib::RefPtr<Gtk::Application> app);
	void run();
};
#endif