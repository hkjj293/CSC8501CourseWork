#pragma once
#include <string>

class User {
public:
	User(std::string name, std::string encryped_pwd) : name(name), encryped_pwd(encryped_pwd) {};
	~User() {};
	std::string name;
	std::string encryped_pwd;
};