#include "GameView.h"
#include "GameController.h"
#include <map>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

template <typename T>
void GameView::printList(vector<T> _cards) {
	for (int n = 0; n < _cards.size(); n++) {
		cout << _cards[n];
		if (n < (_cards.size() - 1)) {
			cout << " ";
		}
	}
	cout << endl;
}

void GameView::printSuit(vector<Card> _cards) {
	vector<Rank> cardsRankList;
	string ranks[RANK_COUNT] = { "A", "2", "3", "4", "5", "6",
		"7", "8", "9", "10", "J", "Q", "K" };

	for (int n = 0; n < _cards.size(); n++) {
		cardsRankList.push_back(_cards[n].getRank());
	}
	sort(cardsRankList.begin(), cardsRankList.end());

	printList(cardsRankList);
}

PlayerType GameView::invitePlayer(int _number) {
	char playerType;
	cout << "Is player " << _number + 1 << " a human(h) or a computer(c)?" << endl;
	cout << ">";
	cin >> playerType;

	if (playerType == 'h') {
		return HUMAN;
	}
	else if (playerType == 'c') {
		return COMPUTER;
	}
	return COMPUTER;
}

void GameView::startRound(int _playerNumber) {
	cout << "A new round begins. It's player " << _playerNumber + 1 << "'s turn to play." << endl;
}

void GameView::printPostGame(const Player& _player) {
	cout << "Player " << _player.getPlayerId() + 1 << " wins!";
}

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

void GameView::startHumanTurn(Player& _human) {
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
	cout << "Legal plays:";
	printList(_human.getLegalMoves());

}

Command GameView::readHumanCommand() {
	cout << ">";
	Command command;
	cin >> command;
	return command;
}

void GameView::printPlayTurn(const Player& player, const Command c) {
	if (c.type_ != PLAY) return;
	cout << "Player " << player.getPlayerId() + 1 << " plays " << c.card_ << "." <<endl;
}

void GameView::printDiscardTurn(const Player& player, const Command c) {
	if (c.type_ != DISCARD) return;
	cout << "Player " << player.getPlayerId() + 1 << " discards " << c.card_ << "." << endl;
}

void GameView::printDeck(const Deck& deck) {
	cout << deck << endl;
}

void GameView::printRageQuit(const Player& player) {
	cout << "Player " << player.getPlayerId() + 1 << " ragequits. A computer will now take over." << endl;
}
