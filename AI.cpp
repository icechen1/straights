#include "AI.h"
#include "Command.h"

using namespace std;

PlayerType AI::getPlayerType() {

}

void AI::play() {
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

	// call display.showAITurn(command)
	return c;
}