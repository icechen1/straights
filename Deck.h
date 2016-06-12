#ifndef _DECK_
#define _DECK_
#include <vector>
#include "Card.h"

class Deck {
	std::vector<Card> cards_;
	const int seed_;
public:
	Deck(int);
	void shuffle();
	std::vector<Card> getCards() const;
};

std::ostream &operator<<(std::ostream &, const Deck &); // to help with debugging

#endif