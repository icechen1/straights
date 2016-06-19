#include "GameView.h"
#include "GameController.h"
#include <map>
#include <algorithm>
#include <string>
#include <iostream>
#include <cassert>

using namespace std;

// requires: T must have a << operator
// ensures: Output a vector of objects
template <typename T>
void GameView::printList(const vector<T> _cards) {
	for (int n = 0; n < _cards.size(); n++) {
		cout << _cards[n];
		if (n < (_cards.size() - 1)) {
			cout << " ";
		}
	}
	cout << endl;
}

// requires: all Cards in the vector are from the same Suit
// ensures: Output cards in a specific suit
void GameView::printSuit(const vector<Card> _cards) {
	vector<Rank> cardsRankList;
	vector<string> output;
	string ranks[RANK_COUNT] = { "A", "2", "3", "4", "5", "6",
		"7", "8", "9", "10", "J", "Q", "K" };

	// Sort the Cards by Rank
	for (int n = 0; n < _cards.size(); n++) {
		cardsRankList.push_back(_cards[n].getRank());
	}
	sort(cardsRankList.begin(), cardsRankList.end());

	// Creat a vector for output
	for (int n = 0; n < cardsRankList.size(); n++) {
		output.push_back(ranks[cardsRankList[n]]);
	}

	printList(output);
}

// return: type of player for the given player number
PlayerType GameView::invitePlayer(const int _number) {
	char c;
	cout << "Is player " << _number + 1 << " a human(h) or a computer(c)?" << endl;
	cout << ">";
	cin >> c;

	assert(c == 'h' || c == 'c');

	if (c == 'h') {
		return HUMAN;
	}
	else if (c == 'c') {
		return COMPUTER;
	}
	return COMPUTER;	// Assume that the user enter a correct value for between h/c
}

// ensures: output a string saying which player stats the round
void GameView::startRound(const Player& _player) {
	cout << "A new round begins. It's player " << _player.getPlayerId() + 1 << "'s turn to play." << endl;
}

// ensures: ouput a string saying which player won the game
void GameView::printWinner(const Player& _player) {
	cout << "Player " << _player.getPlayerId() + 1 << " wins!";
}

// ensures: ouput a string giving the score for the player
void GameView::printPostRound(const Player& _player) {
	cout << "Player " << _player.getPlayerId() + 1 << "'s discards:";
	for (Card c : _player.getDiscards()) {
		cout << " " << c;
	}
	cout << endl;

	int roundScore = _player.getRoundScore();
	int totalScore = _player.getTotalScore();
	int sum = roundScore + totalScore;

	cout << "Player " << _player.getPlayerId() + 1 << "'s score: ";
	cout << totalScore;
	cout << " + ";
	cout << roundScore;
	cout << " = " << sum << endl;
}

// requires: the player is a human player
// ensure: ouput the current information available to the player for his turn
void GameView::startHumanTurn(const Player& _human) {
	shared_ptr<GameController> instance = GameController::getInstance();
	vector<Card> played = instance->getCurrentRound()->getPlayedCard();
	map<Suit, vector<Card>> playedCardsMap;

	for (Card card : played) {
		playedCardsMap[card.getSuit()].push_back(card);
	}
	
	cout << "Cards on the table:" << endl;
	cout << "Clubs: ";
	printSuit(playedCardsMap[CLUB]);
	cout << "Diamonds: ";
	printSuit(playedCardsMap[DIAMOND]);
	cout << "Hearts: ";
	printSuit(playedCardsMap[HEART]);
	cout << "Spades: ";
	printSuit(playedCardsMap[SPADE]);

	cout << "Your hand: ";
	printList(_human.getHand());
	cout << "Legal plays: ";
	printList(_human.getLegalMoves());

}

// Read a command from the user
// returns: a command entered by the user
Command GameView::readHumanCommand() {
	cout << ">";
	Command command;
	cin >> command;
	return command;
}

// requires: the command is a PLAY command
// ensures: ouput the correct command performed by the player when playing a card
void GameView::printPlayTurn(const Player& player, const Command c) {
	if (c.type_ != PLAY) return;
	cout << "Player " << player.getPlayerId() + 1 << " plays " << c.card_ << "." <<endl;
}

// requires: the command is a DISCARD command
// ensures: ouput the correct command performed by the player when discarding a card
void GameView::printDiscardTurn(const Player& player, const Command c) {
	if (c.type_ != DISCARD) return;
	cout << "Player " << player.getPlayerId() + 1 << " discards " << c.card_ << "." << endl;
}

// requires: Deck object must have a defined << operator
// ensures: ouput current deck of cards
void GameView::printDeck(const Deck& deck) {
	cout << deck;
}

// requires: player is a human player
// ensures: ouput message for ragequit
void GameView::printRageQuit(const Player& player) {
	cout << "Player " << player.getPlayerId() + 1 << " ragequits. A computer will now take over." << endl;
}
