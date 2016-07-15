#include "MainMenu.h"
using namespace std;

// requires: seed must be a valid integer
// ensures: a new game is initialized with the given seed and players, and the menu quits
void MainMenu::startGame() {
	bool computer[4];
	for (int i = 0; i < 4; i++) {
		computer[i]= switches_[i]->get_active();
	}
	string seed = entrySeed_->get_text();
	if (seed == "") {
		seed = "0";
	}
	quit();
	view_->startGameWithSettings(std::stoi(seed), computer);
}

// ensures: the menu quits (is hidden)
void MainMenu::quit() {
	assistant_->hide();
}

// requires: valid GaveView needs to be passed in
// ensures: create a new MainMenu (but do not show)
// ensures glade layout is created and all references to GUI widgets are saved
MainMenu::MainMenu(GameView* view) : view_(view) {
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("mainmenu.glade");
	builder->get_widget("menu", assistant_);
	// set references to switches
	for (int i = 0; i < 4; i++) {
		string name = "switch" + std::to_string(i + 1);
		builder->get_widget(name, switches_[i]);
	}
	
	// reference to seed input
	builder->get_widget("entry_seed", entrySeed_);

	// connect handlers
	assistant_->signal_cancel().connect(sigc::mem_fun(*this, &MainMenu::quit));
	assistant_->signal_apply().connect(sigc::mem_fun(*this, &MainMenu::startGame));

	// GTK assistant has next button disabled by default... need to enable that manually
	for (int i = 0; i < 3; i++) {
		assistant_->set_page_complete(*(assistant_->get_nth_page(i)), true);
	}
	// also need to set the last page of the assistant to a confirm button instead of next
	assistant_->set_page_type(*(assistant_->get_nth_page(2)), Gtk::AssistantPageType::ASSISTANT_PAGE_CONFIRM);
}

// ensures: show the main menu dialog
void MainMenu::run() {
	assistant_->show();
}
