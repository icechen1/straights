#ifndef _COMMAND_
#define _COMMAND_

#include "Card.h"
#include <istream>

// enum of possible user commands
enum Type { PLAY, DISCARD, DECK, QUIT, RAGEQUIT, BAD_COMMAND };

struct Command{
	Type type_;
	Card card_;

	Command() : type_(BAD_COMMAND), card_(SPADE, ACE) {} // default constructor - creates bad command
	Command(Type t, Card c) : type_(t), card_(c) {} // creates command with given type and card
};

std::istream &operator>>(std::istream &, Command &); // create command from input

#endif