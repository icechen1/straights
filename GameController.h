#ifndef _GAMECONTROLLER_
#define _GAMECONTROLLER_

#include <memory>
#include <vector>
#include "GameState.h"
#include "Command.h"
#include "Round.h"

// GameController is a singleton entity representing the controller for the Straights game
class GameController {
	static std::shared_ptr<GameController> instance_;	// Hold the instance of the GameController
	std::shared_ptr<GameState> state_;					// Hold information about the state of the Game
														// including players, deck, seed number

	std::shared_ptr<Round> currentRound_;				// Hold the information about the current round that being played
	
	GameController(int);								// Initialize a GameController object
	void initPlayers();									// Initialize a list of 4 players
	void initStartRound();								// Initialize a new round, by creating a round object
	void endRound();									// Proceed to end the round and print the correct information
	bool isGameOver();									// Check if the game is over
	void printWinner() const;							// print the information about the winner
public:
	std::shared_ptr<Player> handleRageQuit(Player & player);	// Replace a human player with an AI player
	static std::shared_ptr<GameController> createInstance(int);	// Create an instance of GameController and save it as static to this class
	static std::shared_ptr<GameController> getInstance();		// Accessor -  get the unique instance of GameController
	std::shared_ptr<Round> getCurrentRound() const;				// Accessor - get the current round information
	std::shared_ptr<GameState> getState() const;				// Accessor - get the current state of the game
	void playRound();											// Play a full round (create, play and end the round)
};

#endif