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
	void printList(std::vector<T>);
	void printSuit(std::vector<Card>);
public:
	char invitePlayer(int);
	void startRound(int);
	Command startHumanTurn(Human&);
	void printPlayTurn(const Player&, const Command) const;
	void printDiscardTurn(const Player&, const Command) const;
};

#endif