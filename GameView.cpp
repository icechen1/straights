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
	cout << "Is player " << _number << " a human(h) or a computer(c)?" << endl;
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
	cout << "A new round begins. It's player " << _playerNumber << "'s turn to play." << endl;
}

Command GameView::startHumanTurn(Player& _human) {
	shared_ptr<GameController> instance = GameController::getInstance();
	vector<Card> played = instance->getState().playedCards_;
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

	Command command;
	cin >> command;
	return command;
}

void GameView::printPlayTurn(const Player& player, const Command c) {
	if (c.type_ != PLAY) return;
	cout << "Player " << player.getPlayerId() << " plays " << c.card_ << endl;
}

void GameView::printDiscardTurn(const Player& player, const Command c) {
	if (c.type_ != DISCARD) return;
	cout << "Player " << player.getPlayerId() << " discards " << c.card_ << endl;
}
