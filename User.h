#pragma once
#include <string>

class User {
public:
	User() : name(""), encryped_pwd("") {};
	User(std::string name, std::string encryped_pwd) : name(name), encryped_pwd(encryped_pwd) {};
	~User() {};
	std::string name;
	std::string encryped_pwd;
	friend bool operator==(const User& lhs, const User& rhs) { return lhs.name == rhs.name; };
	friend bool operator!=(const User& lhs, const User& rhs) { return lhs.name != rhs.name; };
	friend bool operator>=(const User& lhs, const User& rhs) { return lhs.name >= rhs.name; };
	friend bool operator<=(const User& lhs, const User& rhs) { return lhs.name <= rhs.name; };
	friend bool operator>(const User& lhs, const User& rhs) { return lhs.name > rhs.name; };
	friend bool operator<(const User& lhs, const User& rhs) { return lhs.name < rhs.name; };
};