#ifndef _DECK_
#define _DECK_
#include <deque>
#include <memory>
#include "Card.h"

class Deck {
	std::deque<std::shared_ptr<Card>> cards_;
	const int seed_;
public:
	Deck(int);
	void shuffle();
	std::deque<std::shared_ptr<Card>> getCards() const;
};

std::ostream &operator<<(std::ostream &, const Deck &); // to help with debugging

#endif