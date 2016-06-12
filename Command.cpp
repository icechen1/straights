#include "Command.h"
#include <cassert>
#include <sstream>
using namespace std;

istream &operator>>(istream &in, Command &c){
	c.type_ = BAD_COMMAND;

	string str;
	getline(in, str);
	stringstream ss(str);

	string cmd;
	ss >> cmd;

	if (cmd == "play") {
		c.type_ = PLAY;
		ss >> c.card_;
	}
	else if (cmd == "discard_") {
		c.type_ = DISCARD;
		ss >> c.card_;
	}
	else if (cmd == "deck") {
		c.type_ = DECK;
	}
	else if (cmd == "quit") {
		c.type_ = QUIT;
	}
	else if (cmd == "ragequit") {
		c.type_ = RAGEQUIT;
	}

	assert(!in.fail() && !ss.fail() && c.type_ != BAD_COMMAND);

	return in;
}