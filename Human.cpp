#include "Human.h"
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
	GameController::getInstance()->getRecord()->startHumanTurn(*this);
	Command c = GameController::getInstance()->getRecord()->readHumanCommand();
	bool validMove = false;

	while (true) {
		validMove = verify(c);

		if (validMove == true) {
			break;
		}
		else {
			c = GameController::getInstance()->getRecord()->readHumanCommand();
		}
	}
	return c;
}

