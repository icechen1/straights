#include "Human.h"
#include "Command.h"
#include "GameView.h"

using namespace std;

PlayerType Human::getPlayerType() const {
	return HUMAN;
}

Command Human::play() {
	vector<Card> legalMoves = getLegalMoves();
	Command c = Command();
	if (legalMoves.size() > 0) {
		// play the first legal move
		c.type_ = PLAY;
		c.card_ = legalMoves.at(0);
	}
	// discard first card
	c.type_ = PLAY;
	c.card_ = legalMoves.at(0);

	GameView::printPlayTurn(*this, c);
	return c;
}

Command Human::play(const Command _command) const {
	GameView::printPlayTurn(*this, _command);
	return _command;
}