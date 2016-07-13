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
class MainMenu;

class GameView : public Observer {
	template <typename T>
	void printList(std::vector<T>);							// Print a list of object T
	void printSuit(std::vector<Card>);						// Map each card to the correct Suit and print Cards per Suit ordered by Rank
	Glib::RefPtr<Gtk::Application> app_;
	Gtk::Window *window_;
	Gtk::Label *scores_[4];
	Gtk::Label *discards_[4];
	Gtk::Image *cardGrid_[4][13];
	std::shared_ptr<MainMenu> mainMenu_;
	void hideAllCards();
protected:
	void update();
public:
	GameView(Glib::RefPtr<Gtk::Application> app);
	PlayerType invitePlayer(int);							// Prompt the user to determine if a player is human or AI
	void startRound(const Player&);							// Print a message to indicate the start of a round and which player starts
	void printWinner(const Player &);						// Print a message to indicate which player wins
	void printPostRound(const Player&);						// Print information about the round at the end of the round
	void startHumanTurn(const Player&);						// Print information for a human to play his turn
	void printPlayTurn(const Player&, const Command);		// Print information about the played card
	void printDiscardTurn(const Player&, const Command);		// Print information about the discarded card
	void printDeck(const Deck&);								// Print the full Deck
	void printRageQuit(const Player&);						// Print a message informing a human player ragequits
	Command readHumanCommand();								// Prompt a command to the user for a human player
	
	void handleQuit();
	void openMenu();
	int run();
};

#endif