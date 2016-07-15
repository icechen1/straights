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

// View of the main game window - handles GUI logic as well as handling human player actions
class GameView : public Observer {
	// the following are references to GUI elements
	Gtk::Window *window_;
	Gtk::Label *record_;
	Gtk::Label *playerTurnDisplay_;
	Gtk::Viewport *viewport_;
	Gtk::Label *scores_[4];
	Gtk::Label *discards_[4];
	Gtk::Image *cardGrid_[4][13];
	Gtk::Button *hand_[13];
	Gtk::Button *rageQuit_[4];
	Gtk::Image *handImage_[13];

	// reference to the new game window
	MainMenu* mainMenu_;
	sigc::connection AIwatcher_;
	
	void hideAllCards(); // hide all cards from the played card grid
	void disableHandButtons(); // disable all buttons from the player's hand
	void disableRageButtons(); // disable all ragequit buttons
	void clearHand(); // removes cards from hand
	bool playNextAITurn();
protected:
	void update(); // called from subject updates (model)
public:
	GameView();	// constructor - builds the GUI from glade file and fetches appropriate references
	void handleQuit(); // handles quit button
	void openMenu(); // handles new game button
	int run(Glib::RefPtr<Gtk::Application> app); // shows the window
	void startGameWithSettings(int seed, bool computers[]); // handler for a new game creation (Called from menu)
	void initGameRoundWatcher();
	void disconnectWatcher();
	void rageQuit(int n); // handles rage quit button action
	void selectHand(int n); // handles card selection from hand
	void showRoundEndDialog(bool isGameEnd); // handles showing up round/game end message dialog
};

#endif