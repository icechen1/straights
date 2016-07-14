#ifndef _GAMERECORD_
#define _GAMERECORD_
#include <sstream>
#include <vector>
#include <algorithm>
#include <memory>
#include "Player.h"
#include "Deck.h"
#include "GameController.h"
#include "GameState.h"
class GameController;
class GameState;

// stores game history (text records) of each action played in the current game
class GameRecord {
private:
	std::ostringstream output_;								// string stream that stores the game history
	template <typename T>
	void printList(std::vector<T>);							// Print a list of object T
	void printSuit(std::vector<Card>);						// Map each card to the correct Suit and print Cards per Suit ordered by Rank
public:
	void startRound(const Player&);							// Print a message to indicate the start of a round and which player starts
	void printWinner(const Player &);						// Print a message to indicate which player wins
	void printPostRound(const Player&);						// Print information about the round at the end of the round
	void startHumanTurn(const Player&);						// Print information for a human to play his turn
	void printPlayTurn(const Player&, const Command);		// Print information about the played card
	void printDiscardTurn(const Player&, const Command);	// Print information about the discarded card
	void printDeck(const Deck&);							// Print the full Deck
	void printRageQuit(const Player&);						// Print a message informing a human player ragequits
	Command readHumanCommand();								// Prompt a command to the user for a human player
	std::string getOutput() const;							// Retrieve the contents of the game history so far
};
#endif
