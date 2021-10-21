#include "PwdGenRule2.h"
#include <iostream>

PwdGenRule2::PwdGenRule2() : PwdGen() {
	reset_char_bank();
}

PwdGenRule2::~PwdGenRule2() {

}

inline void PwdGenRule2::reset_char_bank() {
	for (int i = 1; i < 256; i++) {
		this->char_bank->push_back((char)i);
	}
}

inline std::string PwdGenRule2::generate(int length) {
	srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	std::string out = "";
	std::vector<char> temp(*(this->char_bank)); 
	if (length > 255) length = 255;
	for (int i = 0; i < length; i++) {
		int seed = rand() % temp.size();
		out += temp[seed];
		temp.erase(temp.begin() + seed);
	}
	return out;
}