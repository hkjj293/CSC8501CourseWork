#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <chrono>
#include "Collatz.h"

class Cracker {
public:
	Cracker() {};
	virtual ~Cracker() {};
	std::string generate(std::string input);
	virtual std::chrono::nanoseconds crack(std::string pwd, std::chrono::nanoseconds dur) = 0;
protected:
	std::string name;
	Collatz collatz;
};