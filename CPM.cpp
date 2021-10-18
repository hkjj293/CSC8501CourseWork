#include<iostream>
#include "CPM.h"

CPM::CPM() {
	this->running = true;
	menu_init();
}

CPM::~CPM() {

}

void CPM::start() {
	while (this->running) {
		menu.show();
		switch (menu.curr_option) {
		case 1:
			create_pwd();
			break;
		case 2:
			auth_pwd();
			break;
		case 3:
			gen_report();
			break;
		case 4:
			analyse_report();
			break;
		case 5:
			break;
		case 6:
			this->running = false;
		}
	}
}

void CPM::menu_init() {
	menu.banner.push_back("++========================================================++");
	menu.banner.push_back("++                 Collatz Password Manager               ++");
	menu.banner.push_back("++========================================================++");
	menu.options.push_back("  1. Create username/password");
	menu.options.push_back("  2. Check username and password");
	menu.options.push_back("  3. Generate password strength analysis file");
	menu.options.push_back("  4. Analys password strength analysis file");
	menu.options.push_back("  5. Decrypt an encrypted password");
	menu.options.push_back("  6. Exit");
}

void CPM::create_pwd() {

}

void CPM::auth_pwd() {

}

void CPM::gen_report() {

}

void CPM::analyse_report() {

}
