#ifndef _COMMAND_
#define _COMMAND_

#include "Card.h"
#include <istream>

enum Type { PLAY, DISCARD, DECK, QUIT, RAGEQUIT, BAD_COMMAND };

struct Command{
	Type type_;
	Card card_;

	Command() : type_(BAD_COMMAND), card_(SPADE, ACE) {}
};

std::istream &operator>>(std::istream &, Command &);

#endif