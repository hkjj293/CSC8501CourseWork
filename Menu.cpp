#include "Menu.h"
#include "CPMOptions.h"
#include <iostream>


Menu::Menu() {
	set_banner();
	set_options();
}

Menu::~Menu() {

}

void Menu::print(){
	for (int i = 0; i < (int)this->banner.size(); i++) {
		std::cout << this->banner[i] << std::endl;
	}
	for (int i = 0; i < (int)this->options.size(); i++) {
		this->options[i]->print();
	}
}

void Menu::choose_option() {
	int input = 0;
	while (input < 1 || input > (int)this->options.size()) {
		std::cout << "Please choose an option above (1-4): ";
		try {
			std::string inp;
			std::cin >> inp;
			input = std::stoi(inp);
		}
		catch (const std::invalid_argument& rte) {
			input = 0;
		}
	}
	(this->options)[input - 1]->run();
}

void Menu::set_banner() {
	this->banner = std::vector<std::string>(3);
	this->banner[0] = "++========================================================++";
	this->banner[1] = "++                 Collatz Password Manager               ++";
	this->banner[2] = "++========================================================++";
}

void Menu::set_options() {
	this->options = std::vector<Option*>(4);
	(this->options)[0] = new Option_1();
	(this->options)[1] = new Option_1();
	(this->options)[2] = new Option_1();
	(this->options)[3] = new Option_1();
}