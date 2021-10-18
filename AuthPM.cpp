#pragma once
#include "AuthPM.h"

AuthPM::~AuthPM() {
	if (this->users != NULL) {
		delete users;
		users = NULL;
	}
}

void AuthPM::create(std::string name, std::string pwd) {
	User user = User(name, this->generate(pwd));
	if (!users->has_element(user)) {
		this->users->add_node(user);
	}

}

void AuthPM::auth(std::string name, std::string pwd) {

}


