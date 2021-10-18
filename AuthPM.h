#pragma once
#include "User.h"
#include "BST.h"
#include "PwdManager.h"

class AuthPM : PwdManager {
public:
	AuthPM() : PwdManager(), users(NULL){};
	~AuthPM();
	void create(std::string name, std::string pwd);
	void auth(std::string name, std::string pwd);
private:
	BST<User>* users;
};