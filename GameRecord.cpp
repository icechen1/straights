#include "GameRecord.h"
using namespace std;

// requires: T must have a << operator
// ensures: Output a vector of objects
template <typename T>
void GameRecord::printList(const vector<T> _cards) {
	for (int n = 0; n < _cards.size(); n++) {
		output_ << _cards[n];
		if (n < (_cards.size() - 1)) {
			output_ << " ";
		}
	}
	output_ << endl;
}

// requires: all Cards in the vector are from the same Suit
// ensures: Output cards in a specific suit
void GameRecord::printSuit(const vector<Card> _cards) {
	vector<Rank> cardsRankList;
	vector<string> output;
	string ranks[RANK_COUNT] = { "A", "2", "3", "4", "5", "6",
		"7", "8", "9", "10", "J", "Q", "K" };

	// Sort the Cards by Rank
	for (int n = 0; n < _cards.size(); n++) {
		cardsRankList.push_back(_cards[n].getRank());
	}
	sort(cardsRankList.begin(), cardsRankList.end());

	// Creat a vector for output
	for (int n = 0; n < cardsRankList.size(); n++) {
		output.push_back(ranks[cardsRankList[n]]);
	}

	printList(output);
}

// ensures: output a string saying which player stats the round
void GameRecord::startRound(const Player& _player) {
	output_ << "A new round begins. It's player " << _player.getPlayerId() + 1 << "'s turn to play." << endl;
}

// ensures: ouput a string saying which player won the game
void GameRecord::printWinner(const Player& _player) {
	output_ << "Player " << _player.getPlayerId() + 1 << " wins!" << endl;
}

// ensures: ouput a string giving the score for the player
void GameRecord::printPostRound(const Player& _player) {
	output_ << "Player " << _player.getPlayerId() + 1 << "'s discards:";
	for (Card c : _player.getDiscards()) {
		output_ << " " << c;
	}
	output_ << endl;

	int roundScore = _player.getRoundScore();
	int totalScore = _player.getTotalScore();
	int sum = roundScore + totalScore;

	output_ << "Player " << _player.getPlayerId() + 1 << "'s score: ";
	output_ << totalScore;
	output_ << " + ";
	output_ << roundScore;
	output_ << " = " << sum << endl;
}

// requires: the player is a human player
// ensure: ouput the current information available to the player for his turn
void GameRecord::startHumanTurn(const Player& _human) {
	shared_ptr<GameState> instance = GameState::getInstance();
	vector<Card> played = instance->getPlayedCards();
	map<Suit, vector<Card>> playedCardsMap;

	for (Card card : played) {
		playedCardsMap[card.getSuit()].push_back(card);
	}

	output_ << "Cards on the table:" << endl;
	output_ << "Clubs: ";
	printSuit(playedCardsMap[CLUB]);
	output_ << "Diamonds: ";
	printSuit(playedCardsMap[DIAMOND]);
	output_ << "Hearts: ";
	printSuit(playedCardsMap[HEART]);
	output_ << "Spades: ";
	printSuit(playedCardsMap[SPADE]);

	output_ << "Your hand: ";
	printList(_human.getHand());
	output_ << "Legal plays: ";
	printList(_human.getLegalMoves());

}

// Read a command from the user
// returns: a command entered by the user
Command GameRecord::readHumanCommand() {
	output_ << ">";
	Command command;
	cin >> command;
	return command;
}

std::string GameRecord::getOutput() const
{
	return output_.str();
}

// requires: the command is a PLAY command
// ensures: ouput the correct command performed by the player when playing a card
void GameRecord::printPlayTurn(const Player& player, const Command c) {
	if (c.type_ != PLAY) return;
	output_ << "Player " << player.getPlayerId() + 1 << " plays " << c.card_ << "." << endl;
}

// requires: the command is a DISCARD command
// ensures: ouput the correct command performed by the player when discarding a card
void GameRecord::printDiscardTurn(const Player& player, const Command c) {
	if (c.type_ != DISCARD) return;
	output_ << "Player " << player.getPlayerId() + 1 << " discards " << c.card_ << "." << endl;
}

// requires: Deck object must have a defined << operator
// ensures: ouput current deck of cards
void GameRecord::printDeck(const Deck& deck) {
	output_ << deck;
}

// requires: player is a human player
// ensures: ouput message for ragequit
void GameRecord::printRageQuit(const Player& player) {
	output_ << "Player " << player.getPlayerId() + 1 << " ragequits. A computer will now take over." << endl;
}

