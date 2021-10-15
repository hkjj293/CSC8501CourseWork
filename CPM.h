#pragma once
#include "User.h"
#include "Menu.h"

class CPM {
public:
	CPM();
	~CPM();
	bool validate(std::string name, std::string pwd);
	bool create_user(std::string name, std::string pwd);
protected:
	std::string collatz_conjecture();
	User* users;
	void load_users();
	void save_users();
};