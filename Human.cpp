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

Command Human::play(const Command _command) const {
	GameView::printPlayTurn(*this, _command);
	return _command;
}