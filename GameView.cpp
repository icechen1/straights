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

GameView::GameView()
{
	Gtk::Button *quitBtn, *newGameBtn;
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("screen.glade");
	auto css = Gtk::CssProvider::create();
	// try to load button styles
	if (!css->load_from_path("style.css")) {
		cerr << "Failed to load css\n";
		std::exit(1);
	}

	builder->get_widget("window1", window_);
	builder->get_widget("quit_btn", quitBtn);
	builder->get_widget("new_game_btn", newGameBtn);

	string suits[] = { "C", "D", "H", "S" };
	string ranks[] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };

	for (int i = 0; i < 4; i++) {
		builder->get_widget("score" + std::to_string(i + 1), scores_[i]);
		builder->get_widget("discards" + std::to_string(i + 1), discards_[i]);
		builder->get_widget("rage" + std::to_string(i + 1), rageQuit_[i]);
		scores_[i]->set_text("0 point");
		discards_[i]->set_text("0 discards");
		rageQuit_[i]->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &GameView::rageQuit), i));
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			builder->get_widget(suits[i] + ranks[j], cardGrid_[i][j]);
		}
	}
	auto screen = Gdk::Screen::get_default();

	for (int k = 0; k < 13; k++) {
		string hand = "hand" + std::to_string(k + 1);
		string handImage = "hand_image" + std::to_string(k + 1);
		builder->get_widget(hand, hand_[k]);
		builder->get_widget(handImage, handImage_[k]);
		// set style
		auto context = hand_[k]->get_style_context();
		context->add_provider_for_screen(screen, css, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
		// set handler for hand buttons
		hand_[k]->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &GameView::selectHand), k));
	}

	// get a ref to the record text field
	builder->get_widget("record", record_);
	builder->get_widget("viewport1", viewport_);

	// disable UI elements when game is not in progress
	hideAllCards();
	clearHand(); 
	disableHandButtons();
	disableRageButtons();

	// connect handlers to new game and quit buttons
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
	shared_ptr<GameState> state_instance = GameState::getInstance();
	shared_ptr<Player> p = state_instance->getCurrentPlayer();
	vector<shared_ptr<Player>> players = state_instance->getPlayers();
	bool gameOver = instance->isGameOver();

	disableRageButtons();
	// update score board
	for (int i = 0; i < 4; i++) {
		// show points
		scores_[i]->set_text(std::to_string(state_instance->getPlayerTotalScore(i)) + " points");
		discards_[i]->set_text(std::to_string(state_instance->getPlayerDiscards(i).size()) + " discards");
		// enable rage button
		if (players.at(i) == p && gameOver == false) {
			// enable rage button for current 
			rageQuit_[i]->set_sensitive(true);
		}
	}
	
	clearHand();

	// use an array to convert rank ordinal to file name
	string ranks[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "j", "q", "k" };
	// update hand
	// TODO: get a helper function for this
	vector<Card> hand = p->getHand();
	vector<Card> legalMoves = p->getLegalMoves();

	disableHandButtons();

	Gdk::RGBA green;
	green.set("#00ff00");
	Gdk::RGBA red;
	red.set("#ff0000");

	for (int i = 0; i < hand.size(); i++) {
		Card c = hand.at(i);
		string filename = "img/" + std::to_string(c.getSuit()) + '_' + ranks[c.getRank()] + ".png";
		handImage_[i]->set(filename);
		// check if it is a legal move
		auto context = hand_[i]->get_style_context();
		if (std::find(legalMoves.begin(), legalMoves.end(), c) != legalMoves.end()) {
			// has legal moves
			hand_[i]->set_opacity(1);
			context->remove_class("invalid");
			context->add_class("play");
		}
		else if (legalMoves.size() == 0) {
			// no legal moves, can only discard
			hand_[i]->set_opacity(1);
			context->remove_class("invalid");
			context->add_class("discard");
		}
		hand_[i]->set_sensitive(true);
	}

	// show card state
	hideAllCards();
	vector<Card> cards = state_instance->getPlayedCards();
	for (Card c : cards) {
		string filename = "img/" + std::to_string(c.getSuit()) + '_' + ranks[c.getRank()] + ".png";
		cardGrid_[c.getSuit()][c.getRank()]->set(filename);
	}

	// update record
	record_->set_text(instance->getRecord()->getOutput());
	// scroll to bottom
	Glib::RefPtr<Gtk::Adjustment> adj = viewport_->get_vadjustment();
	adj->set_value(adj->get_upper());

	if (instance->isRoundEnd() == true) {
		return;
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

void GameView::disableHandButtons() {
	for (int j = 0; j < 13; j++) {
		hand_[j]->set_sensitive(false);
		hand_[j]->set_opacity(0.3f);
		auto context = hand_[j]->get_style_context();
		context->remove_class("play");
		context->remove_class("discard");
		context->add_class("invalid");
	}
}

void GameView::disableRageButtons() {
	for (int j = 0; j < 4; j++) {
		rageQuit_[j]->set_sensitive(false);
	}
}

void GameView::clearHand() {
	for (int j = 0; j < 13; j++) {
		handImage_[j]->set("img/nothing.png");
	}
}

void GameView::startGameWithSettings(int seed, bool computers[]) {
	GameController::createInstance(seed, computers, this);
	shared_ptr<GameController> instance = GameController::getInstance();
	instance->initStartRound();
	instance->playAITurns();
}

void GameView::rageQuit(int n) {
	Command c;
	c.type_ = RAGEQUIT;
	shared_ptr<Player> player = GameState::getInstance()->getPlayers().at(n);
	GameController::getInstance()->getCurrentRound()->playTurn(player, c);
	GameController::getInstance()->playAITurns();
}

void GameView::selectHand(int n) {
	shared_ptr<Player> player = GameState::getInstance()->getCurrentPlayer();
	vector<Card> hand = player->getHand();
	Card selectedCard = hand.at(n);
	bool valid = GameController::getInstance()->playHumanTurn(selectedCard);
	if (!valid) {
		// show invalid move error dialog
		Gtk::MessageDialog dialog(*window_, "Invalid move", false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_OK);
		dialog.set_secondary_text("You may not discard a card when there's a legal move in hand.");
		int result = dialog.run();
	}
}

void GameView::showRoundEndDialog(bool isGameEnd) {
	string title = isGameEnd ? "Game over" : "Round over";
	Gtk::MessageDialog dialog(*window_, title, false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_OK);
	std::ostringstream stream; // pipe output to an output stream for now

	vector<shared_ptr<Player>> winningPlayers;
	vector<shared_ptr<Player>> players = GameState::getInstance()->getPlayers();
	int min = players[0]->getTotalScore();

	for (shared_ptr<Player> player : players) {
		stream << "Player " << player->getPlayerId() + 1 << "'s discards:";
		for (Card c : player->getDiscards()) {
			stream << " " << c;
		}
		stream << endl;

		int roundScore = player->getRoundScore();
		int totalScore = player->getTotalScore();
		int sum = roundScore + totalScore;

		stream << "Player " << player->getPlayerId() + 1 << "'s score: ";
		stream << totalScore;
		stream << " + ";
		stream << roundScore;
		stream << " = " << sum << endl;

		//find winner (if this is game end)
		if (isGameEnd) {
			if (player->getTotalScore() < min) {
				winningPlayers.clear();
				winningPlayers.push_back(player);
				min = player->getTotalScore();
			}
			else if (player->getTotalScore() == min) {
				winningPlayers.push_back(player);
			}
		}

	}
	// print winner
	if (isGameEnd) {
		// print out all winning players
		for (shared_ptr<Player> p : winningPlayers) {
			stream << "Player " << p->getPlayerId() + 1 << " wins!" << endl;
		}
	}

	dialog.set_secondary_text(stream.str());
	int result = dialog.run();
}


