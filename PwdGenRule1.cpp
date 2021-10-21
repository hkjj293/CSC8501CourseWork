#include "PwdGenRule1.h"
#include <iostream>
#include <string>

PwdGenRule1::PwdGenRule1() : PwdGen() {
	for (char ch = 'a'; ch <= 'z'; ch++) {
		this->char_bank->push_back(ch);
	}
}

PwdGenRule1::~PwdGenRule1() {

}

inline std::string PwdGenRule1::generate(int length) {
	std::chrono::nanoseconds nano = std::chrono::high_resolution_clock::now().time_since_epoch();
	srand((unsigned int)nano.count());
	std::string out = "";
	for (int i = 0; i < length; i++) {
		out += (*(this->char_bank))[rand() % char_bank->size()];
	}
	return out;
}