#include "Human.h"
#include "Command.h"
#include "GameView.h"

using namespace std;

PlayerType Human::getPlayerType() const {
	return HUMAN;
}

Command Human::play() {
	return Command();
}

Command Human::playFirstTurn()
{
	Command c = Command();
	c.type_ = PLAY;
	c.card_ = Card(SPADE, SEVEN);
	GameView::printPlayTurn(*this, c);
	return Command();
}
