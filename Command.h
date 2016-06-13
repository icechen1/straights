#ifndef _COMMAND_
#define _COMMAND_

#include "Card.h"
#include <istream>

enum Type { PLAY, DISCARD, DECK, QUIT, RAGEQUIT, BAD_COMMAND };

struct Command{
	Type type_;
	Card card_;

	Command() : type_(BAD_COMMAND), card_(SPADE, ACE) {}
	Command(Type t, Card c) : type_(t), card_(c) {}
};

std::istream &operator>>(std::istream &, Command &);

#endif