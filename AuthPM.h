#pragma once
#include "User.h"
#include "BST.h"
#include "PwdManager.h"
#include <fstream>

class AuthPM : public PwdManager {
public:
	AuthPM();
	virtual ~AuthPM();
	void create(std::string name, std::string pwd);
	int auth(std::string name, std::string pwd);
	void store(std::vector<User>&& usr, std::ifstream::openmode mode);
	virtual void store();
	virtual void load();
private:
	BST<User>* users;
};