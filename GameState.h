#ifndef _GAMESTATE_
#define _GAMESTATE_
#include "Subject.h"
#include "Deck.h"
#include "Player.h"
#include "GameController.h"
#include "RoundController.h"
#include <vector>
#include <memory>
class GameController;
class RoundController;

class GameState : public Subject {
	// Class that holds the information about the game (model)
private:
	static std::shared_ptr<GameState> instance_;	// Hold the instance of the GameState

	std::vector<std::shared_ptr<Player>> players_;	// Hold the pointers to players in the game
	std::shared_ptr<Deck> deck_;					// Hold the pointers to the Deck that is used
	GameState(int _seed) : seed_(_seed) {};			// Construct the GameState
	int seed_;										// Hold the seed number
	// information about current round:
	bool firstTurn_ = true; // defaults to true - set to false after first turn
	std::shared_ptr<Player> currentPlayer_; // list of players in current round, in playing order
	std::vector<Card> playedCards_; // list of cards played by all players
	friend GameController;
	friend RoundController;
public:
	static std::shared_ptr<GameState> createInstance(int seed);	// A Facade method to create a new GameState and use pre set seed
	static std::shared_ptr<GameState> getInstance();		// Accessor -  get the unique instance of GameState
	void setSeed(int);										// Accessor - sets the game seed
	int getSeed() const;									// Mutator - sets the game seed

	void setFirstTurn(bool); // sets the first turn flag of the game
	int getFirstTurn() const; // retrives the first turn flag of the game

	void setPlayers(std::vector<std::shared_ptr<Player>>); // sets the list of players in current game
	std::vector<std::shared_ptr<Player>> getPlayers() const; // retrieves the list of players in current game

	void setCurrentPlayer(std::shared_ptr<Player>); // sets the player in current turn
	std::shared_ptr<Player> getCurrentPlayer() const; // gets the player in current turn

	void setDeck(std::shared_ptr<Deck>); // sets the game deck
	std::shared_ptr<Deck> getDeck() const; // gets the game deck

	void setPlayedCards(std::vector<Card>); // sets the list of played cards in game
	std::vector<Card> getPlayedCards() const; // gets the list of played cards
	void computeTotalScore();	// Calculate the total score of each player
	std::vector<std::shared_ptr<Player>> computeWinners() const;	// Find the list of winners

	// the following methods are facade methods that retrieves a field from a given Player in game (using their index)
	std::vector<Card> getPlayerDiscards(int) const;
	std::vector<Card> getPlayerHand(int) const;
	std::vector<Card> getPlayerLegalMoves(int) const;
	int getPlayerTotalScore(int) const;
	PlayerType getPlayerType(int) const;
};

#endif
