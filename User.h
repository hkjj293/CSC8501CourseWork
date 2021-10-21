#pragma once
#include <string>
#include <iostream>

class User {
public:
	User() : name(""), encryped_pwd("") {};
	User(std::string name, std::string encryped_pwd) : name(name), encryped_pwd(encryped_pwd) {};
	~User() {};
	std::string name;
	std::string encryped_pwd;
	inline bool compare_pwd(User& user_b) { return this->encryped_pwd == user_b.encryped_pwd; };
	friend bool operator==(const User& lhs, const User& rhs) { return lhs.name == rhs.name; };
	friend bool operator!=(const User& lhs, const User& rhs) { return lhs.name != rhs.name; };
	friend bool operator>=(const User& lhs, const User& rhs) { return lhs.name >= rhs.name; };
	friend bool operator<=(const User& lhs, const User& rhs) { return lhs.name <= rhs.name; };
	friend bool operator>(const User& lhs, const User& rhs) { return lhs.name > rhs.name; };
	friend bool operator<(const User& lhs, const User& rhs) { return lhs.name < rhs.name; };
	friend std::ostream& operator<<(std::ostream& os, const User& rhs) { return os << rhs.name << " " << rhs.encryped_pwd << std::endl; };
private:
};