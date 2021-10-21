#include "PwdGenRule1.h"
#include <iostream>
#include <string>
#include <set>

PwdGenRule1::PwdGenRule1() : PwdGen() {
	reset_char_bank();
	reset_char_set();
}

PwdGenRule1::~PwdGenRule1() {
	if (this->char_bank != NULL)
		delete this->char_bank;
}

inline void PwdGenRule1::reset_char_bank() {
	for (char ch = 'a'; ch <= 'z'; ch++) {
		this->char_bank->push_back(ch);
	}
}

inline void PwdGenRule1::reset_char_set() {
	std::vector<char> temp(*(this->char_bank));
	for (int i = 0; i < 10; i++) {
		int seed = rand() % temp.size();
		this->char_set.push_back(temp[seed]);
		temp.erase(temp.begin() + seed);
	}
}

inline std::string PwdGenRule1::generate(int length) {
	reset_char_set();
	srand((unsigned int)std::chrono::high_resolution_clock::now().time_since_epoch().count());
	std::string out = "";
	for (int i = 0; i < length; i++) {
		out += (*(this->char_bank))[rand() % char_bank->size()];
	}
	return out;
}