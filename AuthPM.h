#pragma once
#include "User.h"
#include "BST.h"

class AuthPM {
public:
	AuthPM();
	~AuthPM();
private:
	BST<User>* users;
};