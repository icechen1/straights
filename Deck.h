#ifndef _DECK_
#define _DECK_
#include<vector>
#include "Card.h"

class Deck {
	std::vector<Card> cards;
	const int seed;
public:
	Deck(int seed);
	void shuffle();
	std::vector<Card> getCards() const;
};

#endif