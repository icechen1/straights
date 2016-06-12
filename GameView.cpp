#include "GameView.h"
#include "GameController.h"
#include <map>
#include <algorithm>
#include <string>

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

char GameView::invitePlayer(int _number) {
	char playerType;
	cout << "Is player " << _number << " a human(h) or a computer(c)?" << endl;
	cin >> playerType;
	
	if (playerType == 'h' || playerType == 'c') {
		return playerType;
	}
	return ' ';
}

void GameView::startRound(int _playerNumber) {
	cout << "A new round begins. It's player " << _playerNumber << "'s turn to play." << endl;
}

Command GameView::startHumanTurn(Human _human) {
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
	
	cout << "Legal plays:";
}

void GameView::printPlayTurn(Player& player, Command c) const {
	if (c.type_ != PLAY) return;
	cout << "Player " << player.getPlayerId() << " plays " << c.card_ << endl;
}

void GameView::printDiscardTurn(Player& player, Command c) const {
	if (c.type_ != DISCARD) return;
	cout << "Player " << player.getPlayerId() << " discards " << c.card_ << endl;
}
	printList(_human.getHand());
	cout << "Legal plays:";
	printList(_human.getLegalMoves());

	Command command;
	cin >> command;
	return command;
}