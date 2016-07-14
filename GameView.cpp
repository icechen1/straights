#include "GameView.h"
#include "GameController.h"
#include "MainMenu.h"
#include <map>
#include <algorithm>
#include <string>
#include <iostream>
#include <cassert>
#include <gtkmm.h>
using namespace std;

// requires: T must have a << operator
// ensures: Output a vector of objects
template <typename T>
void GameView::printList(const vector<T> _cards) {
	for (int n = 0; n < _cards.size(); n++) {
		cout << _cards[n];
		if (n < (_cards.size() - 1)) {
			cout << " ";
		}
	}
	cout << endl;
}

// requires: all Cards in the vector are from the same Suit
// ensures: Output cards in a specific suit
void GameView::printSuit(const vector<Card> _cards) {
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

// return: type of player for the given player number
PlayerType GameView::invitePlayer(const int _number) {
	char c;
	cout << "Is player " << _number + 1 << " a human(h) or a computer(c)?" << endl;
	cout << ">";
	cin >> c;

	assert(c == 'h' || c == 'c');

	if (c == 'h') {
		return HUMAN;
	}
	else if (c == 'c') {
		return COMPUTER;
	}
	return COMPUTER;	// Assume that the user enter a correct value for between h/c
}

// ensures: output a string saying which player stats the round
void GameView::startRound(const Player& _player) {
	cout << "A new round begins. It's player " << _player.getPlayerId() + 1 << "'s turn to play." << endl;
}

// ensures: ouput a string saying which player won the game
void GameView::printWinner(const Player& _player) {
	cout << "Player " << _player.getPlayerId() + 1 << " wins!" << endl;
}

// ensures: ouput a string giving the score for the player
void GameView::printPostRound(const Player& _player) {
	cout << "Player " << _player.getPlayerId() + 1 << "'s discards:";
	for (Card c : _player.getDiscards()) {
		cout << " " << c;
	}
	cout << endl;

	int roundScore = _player.getRoundScore();
	int totalScore = _player.getTotalScore();
	int sum = roundScore + totalScore;

	cout << "Player " << _player.getPlayerId() + 1 << "'s score: ";
	cout << totalScore;
	cout << " + ";
	cout << roundScore;
	cout << " = " << sum << endl;
}

// requires: the player is a human player
// ensure: ouput the current information available to the player for his turn
void GameView::startHumanTurn(const Player& _human) {
	shared_ptr<GameController> instance = GameController::getInstance();
	vector<Card> played = instance->getCurrentRound()->getPlayedCard();
	map<Suit, vector<Card>> playedCardsMap;

	for (Card card : played) {
		playedCardsMap[card.getSuit()].push_back(card);
	}
	
	cout << "Cards on the table:" << endl;
	cout << "Clubs: ";
	printSuit(playedCardsMap[CLUB]);
	cout << "Diamonds: ";
	printSuit(playedCardsMap[DIAMOND]);
	cout << "Hearts: ";
	printSuit(playedCardsMap[HEART]);
	cout << "Spades: ";
	printSuit(playedCardsMap[SPADE]);

	cout << "Your hand: ";
	printList(_human.getHand());
	cout << "Legal plays: ";
	printList(_human.getLegalMoves());

}

// Read a command from the user
// returns: a command entered by the user
Command GameView::readHumanCommand() {
	cout << ">";
	Command command;
	cin >> command;
	return command;
}

// requires: the command is a PLAY command
// ensures: ouput the correct command performed by the player when playing a card
void GameView::printPlayTurn(const Player& player, const Command c) {
	if (c.type_ != PLAY) return;
	cout << "Player " << player.getPlayerId() + 1 << " plays " << c.card_ << "." <<endl;
}

// requires: the command is a DISCARD command
// ensures: ouput the correct command performed by the player when discarding a card
void GameView::printDiscardTurn(const Player& player, const Command c) {
	if (c.type_ != DISCARD) return;
	cout << "Player " << player.getPlayerId() + 1 << " discards " << c.card_ << "." << endl;
}

// requires: Deck object must have a defined << operator
// ensures: ouput current deck of cards
void GameView::printDeck(const Deck& deck) {
	cout << deck;
}

// requires: player is a human player
// ensures: ouput message for ragequit
void GameView::printRageQuit(const Player& player) {
	cout << "Player " << player.getPlayerId() + 1 << " ragequits. A computer will now take over." << endl;
}


//-------------------------------BEGIN-----------------------------------------------------------BEGIN----------------------------------------------------------

GameView::GameView()
{
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("screen.glade");
	builder->get_widget("window1", window_);

	Gtk::Button *quitBtn, *newGameBtn;
	builder->get_widget("quit_btn", quitBtn);
	builder->get_widget("new_game_btn", newGameBtn);

	for (int i = 0; i < 4; i++) {
		builder->get_widget("score" + std::to_string(i + 1), scores_[i]);
		builder->get_widget("discards" + std::to_string(i + 1), discards_[i]);
		builder->get_widget("rage" + std::to_string(i + 1), rageQuit_[i]);
		rageQuit_[i]->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &GameView::rageQuit), i));
	}

	string suits[] = { "C", "D", "H", "S" };
	string ranks[] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			builder->get_widget(suits[i] + ranks[j], cardGrid_[i][j]);
		}
	}

	for (int k = 0; k < 13; k++) {
		string hand = "hand" + std::to_string(k + 1);
		string handImage = "hand_image" + std::to_string(k + 1);
		builder->get_widget(hand, hand_[k]);
		builder->get_widget(handImage, handImage_[k]);
		hand_[k]->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &GameView::selectHand), k));
	}

	hideAllCards();
	clearHand();

	quitBtn->signal_clicked().connect(sigc::mem_fun(*this, &GameView::handleQuit));
	newGameBtn->signal_clicked().connect(sigc::mem_fun(*this, &GameView::openMenu));

	mainMenu_ = new MainMenu(this);
}

void GameView::handleQuit()
{
	shared_ptr<GameController> instance = GameController::getInstance();
	//instance->unsubscribe(this);
	window_->hide();
}

void GameView::openMenu(){
	mainMenu_->run();
}

int GameView::run(Glib::RefPtr<Gtk::Application> app) {
	return app->run(*window_);
}

void GameView::update()
{
	shared_ptr<GameController> instance = GameController::getInstance();

	// show points
	for (int i = 0; i < 4; i++) {
		scores_[i]->set_text(std::to_string(instance->getState()->players_[i]->getTotalScore()) + " points");
		discards_[i]->set_text(std::to_string(instance->getState()->players_[i]->getDiscards().size()) + " discards");
	}
	
	clearHand();

	// use an array to convert rank ordinal to file name
	string ranks[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "j", "q", "k" };
	// update hand
	// TODO: get a helper function for this
	shared_ptr<Player> p = instance->getState()->currentRound_->getCurrentPlayer();
	vector<Card> hand = p->getHand();
	vector<Card> legalMoves = p->getLegalMoves();

	for (int i = 0; i < hand.size(); i++) {
		Card c = hand.at(i);
		string filename = "img/" + std::to_string(c.getSuit()) + '_' + ranks[c.getRank()] + ".png";
		handImage_[i]->set(filename);
		// check if it is a legal move
		if (std::find(legalMoves.begin(), legalMoves.end(), c) != legalMoves.end()) {
			hand_[i]->set_opacity(1);
		}
		else {
			hand_[i]->set_opacity(0.5f);
		}
	}

	// show card state
	hideAllCards();
	vector<Card> cards = instance->getState()->currentRound_->getPlayedCard();
	for (Card c : cards) {
		string filename = "img/" + std::to_string(c.getSuit()) + '_' + ranks[c.getRank()] + ".png";
		cardGrid_[c.getSuit()][c.getRank()]->set(filename);
	}
}

// hides all cards in screen
void GameView::hideAllCards() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			cardGrid_[i][j]->set("img/nothing.png");
		}
	}
}

void GameView::clearHand() {
	for (int j = 0; j < 13; j++) {
		handImage_[j]->set("img/nothing.png");
	}
}

void GameView::startGameWithSettings(int seed, bool computers[]) {
	GameController::createInstance(seed, computers, shared_ptr<GameView>(this));
	shared_ptr<GameController> instance = GameController::getInstance();
	instance->playAITurns();
}

void GameView::rageQuit(int n) {
	Command c;
	c.type_ = RAGEQUIT;
	shared_ptr<Player> player = GameController::getInstance()->getState()->players_[n];
	GameController::getInstance()->getState()->currentRound_->playTurn(player, c);
	GameController::getInstance()->getState()->currentRound_->playAITurns();
}

void GameView::selectHand(int n) {
	shared_ptr<Player> player = GameController::getInstance()->getState()->currentRound_->getCurrentPlayer();
	vector<Card> hand = player->getHand();
	vector<Card> validMoves = player->getLegalMoves();
	Card selectedCard = hand.at(n);
	Command c;

	if (std::find(validMoves.begin(), validMoves.end(), selectedCard) != validMoves.end()) {
		c.type_ = PLAY;
		c.card_ = selectedCard;
	}
	else {
		c.type_ = DISCARD;
		c.card_ = selectedCard;
	}

	GameController::getInstance()->getState()->currentRound_->playTurn(player, c);
	GameController::getInstance()->getState()->currentRound_->playAITurns();
}

