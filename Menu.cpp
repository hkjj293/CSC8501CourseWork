#include "Menu.h"
#include <iostream>


Menu::Menu() {
	this->curr_option = 0;
}

Menu::~Menu() {
	
}

void Menu::show(){
	while (this->curr_option < 1 || this->curr_option > (int)this->options.size()) {
		for (int i = 0; i < (int)this->banner.size(); i++) {
			std::cout << this->banner[i] << std::endl;
		}
		for (int i = 0; i < (int)this->options.size(); i++) {
			std::cout << this->options[i] << std::endl;
		}
		if ((int)this->options.size() > 0) {
			std::cout << "Please choose an option above (1-" << this->options.size() << "): ";
			this->curr_option = this->get_input();
		}
		std::cout << std::endl;
	}
}

int Menu::get_input() {
	try {
		std::string inp;
		std::getline(std::cin,inp);
		return(std::stoi(inp));
	}
	catch (...) {
		return 0;
	}
}