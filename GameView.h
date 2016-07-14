#ifndef _GAMEVIEW_
#define _GAMEVIEW_

#include <iostream>
#include <memory>
#include <gtkmm.h>
#include "Command.h"
#include "Player.h"
#include "Human.h"
#include "AI.h"
#include "Deck.h"
#include "MainMenu.h"
#include "GameController.h"
class GameController;
class GameState;
class MainMenu;

class GameView : public Observer {
	Gtk::Window *window_;
	Gtk::Label *record_;
	Gtk::Viewport *viewport_;
	Gtk::Label *scores_[4];
	Gtk::Label *discards_[4];
	Gtk::Image *cardGrid_[4][13];
	Gtk::Button *hand_[13];
	Gtk::Button *rageQuit_[4];
	Gtk::Image *handImage_[13];
	MainMenu* mainMenu_;
	void hideAllCards();
	void disableHandButtons();
	void disableRageButtons();
	void clearHand();
protected:
	void update();
public:
	GameView();	
	void handleQuit();
	void openMenu();
	int run(Glib::RefPtr<Gtk::Application> app);
	void startGameWithSettings(int seed, bool computers[]);

	void rageQuit(int n);

	void selectHand(int n);

	void showRoundEndDialog(bool isGameEnd);

};

#endif