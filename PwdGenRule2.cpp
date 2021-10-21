#include "PwdGenRule2.h"
#include <iostream>

PwdGenRule2::PwdGenRule2() : PwdGen() {
	for (int i = 32; i < 256 ; i++) {
		this->char_bank->push_back((char)i);
	}
}

PwdGenRule2::~PwdGenRule2() {

}

inline std::string PwdGenRule2::generate(int length) {
	std::chrono::nanoseconds nano = std::chrono::high_resolution_clock::now().time_since_epoch();
	srand(nano.count());
	std::string out = "";
	std::vector<char> temp(*(this->char_bank));
	for (int i = 0; i < length; i++) {
		int seed = rand() % temp.size();
		out += temp[seed];
		temp.erase(temp.begin() + seed);
		temp.shrink_to_fit();
	}
	return out;
}