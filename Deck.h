#ifndef _DECK_
#define _DECK_
#include <deque>
#include <memory>
#include "Card.h"

class Deck {
	std::deque<std::shared_ptr<Card>> cards_;	// Deque that holds the Deck of Cards
	const int seed_;							// seed number for shuffling
public:
	Deck(int);		//Initialize a Deck
	void shuffle();	// Shuffle the Deck using the seed number
	std::deque<std::shared_ptr<Card>> getCards() const;	// Accessor - get the list of Cards in correct order
};

std::ostream &operator<<(std::ostream &, const Deck &); // to help with debugging

#endif