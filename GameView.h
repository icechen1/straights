#ifndef _GAMEVIEW_
#define _GAMEVIEW_

#include <iostream>
#include "Command.h"
#include "Player.h"
#include "Human.h"
#include "AI.h"
#include "Deck.h"

class GameView {
	template <typename T>
	static void printList(std::vector<T>);							// Print a list of object T
	static void printSuit(std::vector<Card>);						// Map each card to the correct Suit and print Cards per Suit ordered by Rank
public:
	static PlayerType invitePlayer(int);							// Prompt the user to determine if a player is human or AI
	static void startRound(const Player&);							// Print a message to indicate the start of a round and which player starts
	static void printWinner(const Player &);						// Print a message to indicate which player wins
	static void printPostRound(const Player&);						// Print information about the round at the end of the round
	static void startHumanTurn(const Player&);						// Print information for a human to play his turn
	static void printPlayTurn(const Player&, const Command);		// Print information about the played card
	static void printDiscardTurn(const Player&, const Command);		// Print information about the discarded card
	static void printDeck(const Deck&);								// Print the full Deck
	static void printRageQuit(const Player&);						// Print a message informing a human player ragequits
	static Command readHumanCommand();								// Prompt a command to the user for a human player
};

#endif