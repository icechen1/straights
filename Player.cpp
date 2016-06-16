#include "Player.h"
#include "GameController.h"
#include <algorithm>

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
					if (playerCard.getRank() == playedCard.getRank() + 1
						|| playerCard.getRank() == playedCard.getRank() - 1) {
						legals.push_back(playerCard);
					}
				}
			}
		}
	}

	return legals;
}

vector<Card> Player::getHand() const {
	return cards_;
}

void Player::playCard(Card card) {
	cards_.erase(remove(cards_.begin(), cards_.end(), card), cards_.end());
}

void Player::discardCard(Card card) {
	playCard(card);
	discards_.push_back(card);
}

Player::Player(int id) : id_(id){}

int Player::getPlayerId() const {
	return id_;
}

void Player::nextRound() {
	total_score_ += getRoundScore();
	cards_.clear();
	discards_.clear();
}

vector<Card> Player::getDiscards() const {
	return discards_;
}

int Player::getRoundScore() const {
	int round_score = 0;
	for (Card c : discards_) {
		round_score += c.getRank();
	}

	return round_score;
}

int Player::getTotalScore() const {
	return total_score_;
}
