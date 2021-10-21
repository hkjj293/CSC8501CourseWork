#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <chrono>

class PwdGen {
public:
	PwdGen() : char_bank(new std::vector<char>()) { };
	virtual ~PwdGen() { delete char_bank; };
	virtual std::string generate(int length) = 0;
protected:
	std::vector<char>* char_bank;
};