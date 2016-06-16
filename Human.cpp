#include "Human.h"
#include "Command.h"
#include "GameView.h"
#include "GameController.h"

using namespace std;

PlayerType Human::getPlayerType() const {
	return HUMAN;
}

Command Human::play() {
	GameView::startHumanTurn(*this);
	Command c = GameView::readHumanCommand();
	bool validMove = false;

	while (true) {
		switch (c.type_) {
		case PLAY:
			if (find(legalMoves_.begin(), legalMoves_.end(), c.card_) == legalMoves_.end()){
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
			shared_ptr<Deck> deck = GameController::getInstance()->getState().deck_;
			GameView::printDeck(*deck);
			validMove = true;
			break;
		case QUIT:
			validMove = true;
		case RAGEQUIT:
			validMove = true;
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

