#include "GameView.h"

using namespace std;

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

Command GameView::startTurn(Player) {

}