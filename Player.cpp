#include "Player.h"
#include "GameController.h"
#include <algorithm>

using namespace std;

void Player::dealCard(Card c) {
	cards_.push_back(c);
}

void Player::computeLegalMoves(bool firstTurn_) {
	legalMoves_.clear();
	shared_ptr<GameController> instance = GameController::getInstance();
	vector<Card> played = instance->getCurrentRound()->getPlayedCard();

	if (firstTurn_ == true) {
		Card sevenSpade = Card(SPADE, SEVEN);
		legalMoves_.push_back(sevenSpade);
		return;
	}

	for (Card playerCard : cards_) {
		if (playerCard.getRank() == Rank::SEVEN) {
			// any seven of any suit is a legal move
			legalMoves_.push_back(playerCard);
		}
		else {
			for (Card playedCard : played) {
				// look for adjacent cards of same suit
				if (playerCard.getSuit() == playedCard.getSuit()) {
					if (playerCard.getRank() == playedCard.getRank() + 1
						|| playerCard.getRank() == playedCard.getRank() - 1) {
						legalMoves_.push_back(playerCard);
					}
				}
			}
		}
	}
}

std::vector<Card> Player::getLegalMoves() const {
	return legalMoves_;
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

Player::Player(Player &other)
{
	total_score_ = other.total_score_;
	discards_ = vector<Card>(other.discards_);
	cards_ = vector<Card>(other.cards_);
	legalMoves_ = vector<Card>(other.legalMoves_);
	id_ = other.id_;
}

int Player::getPlayerId() const {
	return id_;
}

void Player::clearHand() {
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
		round_score += c.getPointValue();
	}

	return round_score;
}

int Player::getTotalScore() const {
	return total_score_;
}
