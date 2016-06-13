#include "Player.h"
#include "GameController.h"
using namespace std;

void Player::dealCard(Card c) {
	cards_.push_back(c);
}

vector<Card> Player::getLegalMoves() const {
	vector<Card> legals;
	shared_ptr<GameController> instance = GameController::getInstance();
	vector<Card> played = instance->getState().playedCards_;

	for (Card playerCard : cards_) {
		if (playerCard.getRank() == Rank::SEVEN) {
			// any seven of any suit is a legal move
			legals.push_back(playerCard);
		}
		else {
			for (Card playedCard : played) {
				// look for adjacent cards of same suit
				if (playerCard.getSuit() == playedCard.getSuit()) {
					/*TODO FINISH THIS*/
				}
			}
		}
	}

	return legals;
}

vector<Card> Player::getHand() const {
	return cards_;
}

void Player::playCard(Card card)
{
	int position = find(cards_.begin(), cards_.end(), card) - cards_.begin();
	cards_.erase(cards_.begin() + position);
}

void Player::discardCard(Card card)
{
	playCard(card);
	score_ += card.getRank();
}

Player::Player(int id) : id_(id)
{

}

int Player::getPlayerId() const
{
	return id_;
}

int Player::getScore() const
{
	return score_;
}
