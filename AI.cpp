#include "AI.h"

using namespace std;

// returns: human type player constant
PlayerType AI::getPlayerType() const {
	return COMPUTER;
}

// requires: needs cards to be dealt, and still have cards on hand
// ensures: always returns a move
// returns: move (command) for this turn
Command AI::play() {
	vector<Card> legalMoves = getLegalMoves();
	Command c = Command();
	if (legalMoves.size() > 0) {
		// play the first legal move
		c.type_ = PLAY;
		c.card_ = legalMoves.at(0);
	} else {
		// discard first card
		c.type_ = DISCARD;
		c.card_ = cards_.at(0);
	}

	return c;
}
