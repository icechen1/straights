#include "GameState.h"
using namespace std;

std::shared_ptr<GameState> GameState::createInstance(int seed)
{
	instance_ = shared_ptr<GameState>(new GameState(seed));
	return instance_;
}

std::shared_ptr<GameState> GameState::getInstance()
{
	return instance_;
}

void GameState::setSeed(int seed)
{
	seed_ = seed;
}

int GameState::getSeed() const
{
	return seed_;
}

void GameState::setFirstTurn(bool first)
{
	firstTurn_ = first;
}

int GameState::getFirstTurn() const
{
	return firstTurn_;
}

void GameState::setPlayers(std::vector<std::shared_ptr<Player>> players)
{
	players_ = players;
}

std::vector<std::shared_ptr<Player>> GameState::getPlayers() const
{
	return players_;
}

void GameState::setCurrentPlayer(std::shared_ptr<Player> current)
{
	currentPlayer_ = current;
}

std::shared_ptr<Player> GameState::getCurrentPlayer() const
{
	return currentPlayer_;
}

void GameState::setDeck(std::shared_ptr<Deck> deck)
{
	deck_ = deck;
}

std::shared_ptr<Deck> GameState::getDeck() const
{
	return deck_;
}

void GameState::setPlayedCards(std::vector<Card> playedcards)
{
	playedCards_ = playedcards;
}

std::vector<Card> GameState::getPlayedCards() const
{
	return playedCards_;
}

std::vector<Card> GameState::getPlayerDiscards(int playerNo)
{
	return players_.at(playerNo)->getDiscards();
}

std::vector<Card> GameState::getPlayerHand(int playerNo)
{
	return players_.at(playerNo)->getHand();
}

int GameState::getPlayerTotalScore(int playerNo)
{
	return players_.at(playerNo)->getTotalScore();

}

std::vector<Card> GameState::getPlayerLegalMoves(int playerNo)
{
	return players_.at(playerNo)->getLegalMoves();
}

PlayerType GameState::getPlayerType(int playerNo)
{
	return players_.at(playerNo)->getPlayerType();
}

int GameState::getPlayerId(int playerNo)
{
	return players_.at(playerNo)->getPlayerId();

}
