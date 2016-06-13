#include "AI.h"
#include "Command.h"
#include "GameView.h"

using namespace std;

PlayerType AI::getPlayerType() const {
	return COMPUTER;
}

Command AI::play() {
	vector<Card> legalMoves = getLegalMoves();
	Command c = Command();
	if (legalMoves.size() > 0) {
		// play the first legal move
		c.type_ = PLAY;
		c.card_ = legalMoves.at(0);
	}
	// discard first card
	c.type_ = PLAY;
	c.card_ = cards_.at(0);

	GameView::printPlayTurn(*this, c);
	return c;
}