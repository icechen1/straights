#include "GameState.h"
using namespace std;

// requires: valid seed value (integer)
// ensures: creates a singleton instance of GameState with the given seed
// returns: pointer to the created GameState
std::shared_ptr<GameState> GameState::createInstance(int seed)
{
	instance_ = shared_ptr<GameState>(new GameState(seed));
	return instance_;
}

// returns: pointer to the created GameState or nullptr if none found
std::shared_ptr<GameState> GameState::getInstance()
{
	return instance_;
}

// modifies: game seed
void GameState::setSeed(int seed)
{
	seed_ = seed;
}

// returns: game seed
int GameState::getSeed() const
{
	return seed_;
}

// modifies: first turn boolean flag
void GameState::setFirstTurn(bool first)
{
	firstTurn_ = first;
}

// returns: first turn boolean flag
int GameState::getFirstTurn() const
{
	return firstTurn_;
}

// modifies: player list
void GameState::setPlayers(std::vector<std::shared_ptr<Player>> players)
{
	players_ = players;
}

// returns: player list
std::vector<std::shared_ptr<Player>> GameState::getPlayers() const
{
	return players_;
}

// modifies: pointer to current player
//			 notify the observer to change the view
void GameState::setCurrentPlayer(std::shared_ptr<Player> current)
{
	currentPlayer_ = current;
	notify();
}

// returns: pointer to current player
std::shared_ptr<Player> GameState::getCurrentPlayer() const
{
	return currentPlayer_;
}

// modifies: pointer to game deck
void GameState::setDeck(std::shared_ptr<Deck> deck)
{
	deck_ = deck;
}

// returns: pointer to game deck
std::shared_ptr<Deck> GameState::getDeck() const
{
	return deck_;
}

// modifies: vector of played cards in this round
void GameState::setPlayedCards(std::vector<Card> playedcards)
{
	playedCards_ = playedcards;
}

// returns: vector of played cards in this round
std::vector<Card> GameState::getPlayedCards() const
{
	return playedCards_;
}

// returns: vector of discards in this round for given player id
std::vector<Card> GameState::getPlayerDiscards(int playerNo) const
{
	return players_.at(playerNo)->getDiscards();
}

// returns: vector of cards in hard in this round for given player id
std::vector<Card> GameState::getPlayerHand(int playerNo) const
{
	return players_.at(playerNo)->getHand();
}

// returns: player total score for given player id
int GameState::getPlayerTotalScore(int playerNo) const
{
	return players_.at(playerNo)->getTotalScore();

}

// returns: player total score for given player id
std::vector<Card> GameState::getPlayerLegalMoves(int playerNo) const
{
	return players_.at(playerNo)->getLegalMoves();
}

// returns: player type for given player id
PlayerType GameState::getPlayerType(int playerNo) const
{
	return players_.at(playerNo)->getPlayerType();
}

// requires: end of a round or end of a game
// modifies: total score of each player
//			 notify the UI to update the total score
void GameState::computeTotalScore() {
	for (shared_ptr<Player> p : players_) {
		p->calculateTotalScore();
	}
	notify();
}

// requires: end of the game
// returns: list of winning players
vector<shared_ptr<Player>> GameState::computeWinners() const {
	int min = getPlayerTotalScore(0);
	vector<shared_ptr<Player>> winningPlayers;
	for (shared_ptr<Player> p : players_) {
		//find winner
		if (p->getTotalScore() < min) {
			winningPlayers.clear();
			winningPlayers.push_back(p);
			min = p->getTotalScore();
		}
		else if (p->getTotalScore() == min) {
			winningPlayers.push_back(p);
		}
	}
	return winningPlayers;
}
