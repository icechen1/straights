#include "GameView.h"
#include "GameController.h"
#include <map>

using namespace std;

void GameView::printCardList(vector<Card> _cards) {
	for (int n = 0; n < _cards.size(); n++) {
		cout << _cards[n];
		if (n < (_cards.size() - 1)) {
			cout << " ";
		}
	}
	cout << endl;
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
	printCardList(playedCardsMap[CLUB]);
	cout << "Diamonds: ";
	printCardList(playedCardsMap[DIAMOND]);
	cout << "Hearts: ";
	printCardList(playedCardsMap[HEART]);
	cout << "Spades: ";
	printCardList(playedCardsMap[SPADE]);

	cout << "Your hand: ";
	
	cout << "Legal plays:";
}