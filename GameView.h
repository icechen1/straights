#ifndef _GAMEVIEW_
#define _GAMEVIEW_

#include <iostream>
#include "Command.h"
#include "Player.h"
#include "GameState.h"
#include "human.h"
#include "AI.h"

class GameView {
	template <typename T>
	static void printList(std::vector<T>);
	static void printSuit(std::vector<Card>);
public:
	static PlayerType invitePlayer(int);
	static void startRound(int);
	static Command startHumanTurn(Player&);
	static void printPlayTurn(const Player&, const Command);
	static void printDiscardTurn(const Player&, const Command);
	static void printDeck();
	static void printRageQuit(const Player&);
};

#endif