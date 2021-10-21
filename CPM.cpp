#include<iostream>
#include "CPM.h"

CPM::CPM() {
	this->running = true;
	menu_init();
}

CPM::~CPM() {

}

void CPM::init() {

}

void CPM::loop() {
	while (this->running) {
		std::cout << std::endl;
		menu.show();
		switch (menu.curr_option) {
		case 1:
			create_pwd();
			break;
		case 2:
			auth_pwd();
			break;
		case 3:
			gen_file();
			break;
		case 4:
			analyse_file();
			break;
		case 5:
			break;
		case 6:
			this->running = false;
		}
		menu.curr_option = 0;
	}
}

void CPM::start() {
	init();
	loop();
}

void CPM::stop() {
	this->running = false;
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
	std::string name, pwd;
	std::cout << "Input a new username: ";
	std::getline(std::cin, name);
	std::cout << "Input a new password: ";
	std::getline(std::cin, pwd);
	this->auth_pm.create(name, pwd);
}

void CPM::auth_pwd() {
	std::string name, pwd;
	int i = 3;
	std::cout << "Input your username: ";
	std::getline(std::cin, name);
	while (i > 0) {
		std::cout << "Input your password (You have " << i-- << " times left.): ";
		std::getline(std::cin, pwd);
		if (this->auth_pm.auth(name, pwd) > 0) { break; }
	}
}

void CPM::gen_file() {
	this->analyst_pm.gen_rand_pwd(1,100,100);
	this->analyst_pm.store();
}

void CPM::analyse_file() {
	std::chrono::seconds dur(1);
	this->analyst_pm.test(1, 100, 100, (std::chrono::nanoseconds)dur);
}


