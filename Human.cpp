#include "Human.h"
#include "Command.h"
#include "GameView.h"
#include "GameController.h"

using namespace std;

// returns: human type player constant
PlayerType Human::getPlayerType() const {
	return HUMAN;
}

// requires: needs cards to be dealt, and still have cards on hand
// ensures: always returns a move
// returns: move (command) for this turn
Command Human::play() {
	GameView::startHumanTurn(*this);
	Command c = GameView::readHumanCommand();
	shared_ptr<Deck> deck = GameController::getInstance()->getState()->deck_;

	bool validMove = false;

	while (true) {
		switch (c.type_) {
		case PLAY:
			if (find(legalMoves_.begin(), legalMoves_.end(), c.card_) != legalMoves_.end()){
				validMove = true;
			}
			else {
				cout << "This is not a legal play." << endl;
			}
			break;
		case DISCARD:
			if (legalMoves_.empty()) {
				validMove = true;
			}
			else {
				cout << "You have a legal play. You may not discard." << endl;
			}
			break;
		case DECK:
			GameView::printDeck(*deck);
			break;
		case QUIT:
			throw c;
			break;
		case RAGEQUIT:
			validMove = true;
			break;
		default:
			break;
		}

		if (validMove == true) {
			break;
		}
		else {
			c = GameView::readHumanCommand();
		}
	}
	return c;
}

