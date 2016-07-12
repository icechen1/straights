#include "MainMenu.h"
#include <iostream>
using namespace std;

void MainMenu::startGame() {
	bool computer[4];
	for (int i = 0; i < 4; i++) {
		computer[i]= switches_[i]->get_active();
	}
	quit();
}

void MainMenu::quit() {
	assistant_->hide();
}

MainMenu::MainMenu(Glib::RefPtr<Gtk::Application> app) : app_(app) {
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("mainmenu.glade");
	builder->get_widget("menu", assistant_);
	// set references to switches
	for (int i = 0; i < 4; i++) {
		string name = "switch" + std::to_string(i + 1);
		builder->get_widget(name, switches_[i]);
	}
	assistant_->signal_cancel().connect(sigc::mem_fun(*this, &MainMenu::quit));
	// assistant_->signal_close().connect(sigc::mem_fun(*this, &MainMenu::quit));
	assistant_->signal_apply().connect(sigc::mem_fun(*this, &MainMenu::startGame));

	for (int i = 0; i < 2; i++) {
		assistant_->set_page_complete(*(assistant_->get_nth_page(i)), true);
	}
	assistant_->set_page_type(*(assistant_->get_nth_page(1)), Gtk::AssistantPageType::ASSISTANT_PAGE_CONFIRM);
}

void MainMenu::run() {
	assistant_->show();
}
