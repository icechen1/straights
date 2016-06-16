#ifndef _GAMECONTROLLER_
#define _GAMECONTROLLER_

#include <memory>
#include <vector>
#include "GameState.h"
#include "Command.h"
#include "Round.h"

// GameController is a singleton entity representing the controller for the Straights game
class GameController {
	static std::shared_ptr<GameController> instance_;
	GameState state_;

	std::shared_ptr<Round> currentRound_;
	
	GameController(int);
	
	void initPlayers();
	void endRound();
	bool isGameOver();
	void initStartRound();
	void printWinner() const;
public:
	void handleRageQuit(Player & player);
	static std::shared_ptr<GameController> createInstance(int);
	static std::shared_ptr<GameController> getInstance();
	std::shared_ptr<Round> getCurrentRound() const;
	GameState getState() const;
	void playGame();
};

#endif