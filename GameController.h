#ifndef _GAMECONTROLLER_
#define _GAMECONTROLLER_

#include <memory>
#include <vector>
#include "Command.h"
#include "RoundController.h"
#include "Player.h"
#include "Deck.h"
#include "Observer.h"
#include "GameRecord.h"
#include "GameState.h"
#include "GameView.h"
class GameView;
class GameRecord;
class RoundController;
class GameState;

// GameController is a singleton entity representing the controller for the Straights game
class GameController {
	GameView* view_;
	std::unique_ptr<GameRecord> record_;				// Process the play history of the game
	static std::shared_ptr<GameController> instance_;	// Hold the instance of the GameController
	std::unique_ptr<RoundController> roundController_;	// Hold the instance of the RoundController
	GameController(int, GameView*);						// Initialize a GameController object
	void endRound();									// Proceed to end the round and print the correct information
	void printWinner() const;							// print the information about the winner
	void setPlayers(bool[]);							// set players from a bool array (true = computer)
public:
	std::shared_ptr<Player> handleRageQuit(Player & player);	// Replace a human player with an AI player
	static std::shared_ptr<GameController> createInstance(int, bool[], GameView*);	// A Facade method to create a new GameController and use pre set human/computer settings
	static std::shared_ptr<GameController> getInstance();		// Accessor -  get the unique instance of GameController
	RoundController* getCurrentRound() const;					// Accessor - get the current round information
	std::shared_ptr<GameState> getState() const;				// Accessor - get the current state of the game
	GameView* getView() const;									// Accessor - get the view of the game
	GameRecord* getRecord() const;								// Accessor - get the record buffer of the game
	void playAITurns();											// Play a full round (create, play and end the round)
	bool playHumanTurn(Card);									// Play a human turn - called from GUI
	void initStartRound();										// Initialize a new round, by creating a round object
	bool isRoundEnd();											// Check if the round is over
	bool isGameOver();											// Check if the game is over
};

#endif