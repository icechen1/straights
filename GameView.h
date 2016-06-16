#ifndef _GAMEVIEW_
#define _GAMEVIEW_

#include <iostream>
#include "Command.h"
#include "Player.h"
#include "GameState.h"
#include "Human.h"
#include "AI.h"

class GameView {
	template <typename T>
	static void printList(std::vector<T>);
	static void printSuit(std::vector<Card>);
public:
	static PlayerType invitePlayer(int);
	static void startRound(int);
	static void printPostGame(const Player & _player);
	static void printPostRound(const Player&);
	static Command startHumanTurn(Player&);
	static void printPlayTurn(const Player&, const Command);
	static void printDiscardTurn(const Player&, const Command);
	static void printDeck(const Deck&);
	static void printRageQuit(const Player&);
};

#endif