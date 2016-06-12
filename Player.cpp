#include "Player.h"
#include "GameController.h"
using namespace std;

vector<Card> Player::getLegalMoves() const {
	vector<Card> legals;
	shared_ptr<GameController> instance = GameController::getInstance();
	vector<Card> played = instance->getState().playedCards_;

	for (Card playerCard : cards) {
		if (playerCard.getRank() == Rank::SEVEN) {
			// any seven of any suit is a legal move
			legals.push_back(playerCard);
		}
		else {
			for (Card playedCard : played) {
				// look for adjacent cards of same suit
				if (playerCard.getSuit() == playedCard.getSuit()) {

				}
			}
		}
	}

	return legals;
}