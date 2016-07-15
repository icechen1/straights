#include "Player.h"
#include "GameController.h"
#include <algorithm>

using namespace std;

// requires: a valid card
// modifies: adds the card to the set of cards that the player has
// ensures: the card is added to the end of the cards list
void Player::dealCard(Card c) {
	cards_.push_back(c);
}

// requires: first turn or not (rules are different)
// ensures: does not edit the class state
// returns: list of legal moves
std::vector<Card> Player::getLegalMoves() const {
	vector<Card> legalMoves;
	shared_ptr<GameState> instance = GameState::getInstance();
	vector<Card> played = instance->getPlayedCards();

	if (instance->getFirstTurn() == true) {
		Card sevenSpade = Card(SPADE, SEVEN);
		legalMoves.push_back(sevenSpade);
		return legalMoves;
	}

	for (Card playerCard : cards_) {
		if (playerCard.getRank() == Rank::SEVEN) {
			// any seven of any suit is a legal move
			legalMoves.push_back(playerCard);
		}
		else {
			for (Card playedCard : played) {
				// look for adjacent cards of same suit
				if (playerCard.getSuit() == playedCard.getSuit()) {
					if (playerCard.getRank() == playedCard.getRank() + 1
						|| playerCard.getRank() == playedCard.getRank() - 1) {
						legalMoves.push_back(playerCard);
					}
				}
			}
		}
	}
	return legalMoves;
}

// requires: hand must have been first dealt by Round
// ensures: does not edit the class state
// returns: list of cards in hand
vector<Card> Player::getHand() const {
	return cards_;
}

// requires: a valid card in the player's hand
// modifies: removed specified card from list of cards on hand
// ensures: the ordering of the list is preserved
void Player::playCard(Card card) {
	cards_.erase(remove(cards_.begin(), cards_.end(), card), cards_.end());
}

// requires: a valid card in the player's hand
// modifies: removed specified card from list of cards on hand, adds the card to discard list
// ensures: the ordering of the list is preserved
void Player::discardCard(Card card) {
	playCard(card);
	discards_.push_back(card);
}

// requires: valid integer id between 0 to 3
// ensures: set initial player id and empty hand
// returns: a constructed Player object with specified id 
Player::Player(int id) : id_(id){}

// requires: valid other to copy from
// ensures: copies all player properties over
// returns: a constructed Player object with specified id and state
Player::Player(Player &other)
{
	total_score_ = other.total_score_;
	discards_ = vector<Card>(other.discards_);
	cards_ = vector<Card>(other.cards_);
	id_ = other.id_;
}

// ensures: does not edit the class state
// returns: player id
int Player::getPlayerId() const {
	return id_;
}

// modifies: clears list of cards and discards after a round. adds round score to total
void Player::clearHand() {
	total_score_ += getRoundScore();
	cards_.clear();
	discards_.clear();
}

// ensures: does not edit the class state
// returns: list of discarded cards
vector<Card> Player::getDiscards() const {
	return discards_;
}

// ensures: does not edit the class state
// returns: score for this round for the given player
int Player::getRoundScore() const {
	int round_score = 0;
	for (Card c : discards_) {
		round_score += c.getPointValue();
	}

	return round_score;
}

// ensures: does not edit the class state
// returns: score for all rounds for the given player
int Player::getTotalScore() const {
	return total_score_;
}

using namespace std;

// requires: a command
// ensures: the provided command describes a legal move or action
// returns: true if the provided play is valid, false otherwise
bool Player::verify(const Command c) const {
	shared_ptr<Deck> deck = GameState::getInstance()->getDeck();
	vector<Card> legalMoves = getLegalMoves();
	bool validMove = false;
	switch (c.type_) {
	case PLAY:
		if (find(legalMoves.begin(), legalMoves.end(), c.card_) != legalMoves.end()) {
			validMove = true;
		}
		else {
			cout << "This is not a legal play." << endl;
		}
		break;
	case DISCARD:
		if (legalMoves.empty()) {
			validMove = true;
		}
		else {
			cout << "You have a legal play. You may not discard." << endl;
		}
		break;
	case DECK: // no longer valid
	case QUIT:
		return false;
	case RAGEQUIT:
		validMove = true;
		break;
	default:
		break;
	}
	return validMove;
}
