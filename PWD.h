#pragma once
#include <string>
#include <iostream>
#include <chrono>

class PWD {
public:
	PWD() : time(0){};
	~PWD() {};
	std::chrono::nanoseconds time;
	std::string pwd;
private:
};