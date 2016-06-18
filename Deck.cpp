#include "Deck.h"
#include <random>

using namespace std;

// returns a ordered Deck with with a seed number
Deck::Deck(int _seed) : seed_(_seed) {
	Suit suits[4] = { CLUB, DIAMOND, HEART, SPADE };
	Rank ranks[13] = { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN,
		EIGHT, NINE, TEN, JACK, QUEEN, KING };

	for (int i = 0; i < 4; i++) {
		// go through the 4 suits
		for (int j = 0; j < 13; j++) {
			// 13 ranks per suit
			shared_ptr<Card> c(new Card(suits[i], ranks[j]));
			cards_.push_back(c);
		}
	}
}

/* To ensure that the your cards are ordered the same way as
the given program, use this shuffling algorithm.

CARD_COUNT is the constant 52
cards_ is an array of pointers to cards
*/

// requires: a valid Deck objects containing 52 cards
// modifies: change the order of Cards in the Deck
void Deck::shuffle() {
	static mt19937 rng(seed_);

	int n = CARD_COUNT;

	while (n > 1) {
		int k = (int)(rng() % n);
		--n;
		shared_ptr<Card> c = (cards_[n]);
		cards_[n] = cards_[k];
		cards_[k] = c;
	}
}

// requires: a valid Deck objects containing 52 cards
// returns: a deque of Cards in the Deck
deque<shared_ptr<Card>> Deck::getCards() const {
	return cards_;
}

// requires: a valid Deck objects containing 52 cards
// returns: output all the Cards in the Deck, 13 cards per row
std::ostream &operator<<(std::ostream &out, const Deck &deck) {
	int count = 0;
	for (shared_ptr<Card> card : deck.getCards()) {
		out << *card;
		count++;

		if (count != 13) {
			out << " ";
		} else {
			out << endl;
			count = 0;
		}
	}
	return out;
}