#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <chrono>
#include "Collatz.h"
#include "PWD.h"

class Cracker {
public:
	Cracker() {};
	virtual ~Cracker() {};
	std::string generate(std::string input);
	virtual PWD crack(std::string& pwd, std::chrono::nanoseconds& dur) = 0;
	std::string name;
protected:
	Collatz collatz;
};