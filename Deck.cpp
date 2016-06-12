#include "Deck.h"
#include <random>

using namespace std;

Deck::Deck(int seed) : seed(seed) {
	Suit suits[4] = { CLUB, DIAMOND, HEART, SPADE };
	Rank ranks[13] = { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN,
		EIGHT, NINE, TEN, JACK, QUEEN, KING };

	for (int i = 0; i < 4; i++) {
		// go through the 4 suits
		for (int j = 0; j < 13; j++) {
			// 13 ranks per suit
			cards.push_back(Card(suits[i], ranks[j]));
		}
	}
}

/* To ensure that the your cards are ordered the same way as
the given program, use this shuffling algorithm.

CARD_COUNT is the constant 52
cards_ is an array of pointers to cards
*/
void Deck::shuffle() {
	static mt19937 rng(seed);

	int n = CARD_COUNT;

	while (n > 1) {
		int k = (int)(rng() % n);
		--n;
		Card *c = cards_[n];
		cards_[n] = cards_[k];
		cards_[k] = c;
	}
}

vector<Card> Deck::getCards() const {
	return cards;
}

