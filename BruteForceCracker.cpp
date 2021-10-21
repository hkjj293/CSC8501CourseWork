#include "BruteForceCracker.h"
#include <vector>
using namespace std::chrono;

void pwd_plus_one(std::string& pwd) {
	pwd[0] ++;
	for (int i = 0; i < pwd.size() - 1; i++) {
		if (pwd[i] == 0) {
			pwd[i] = 32;
			pwd[i + 1]++;
		}
	}
	if (pwd[pwd.size() - 1] == 0) {
		pwd[pwd.size() - 1] = 32;
		pwd.push_back(32);
	}	
}

BruteForceCracker::BruteForceCracker() {
	this->name = "Brute Force";
}

BruteForceCracker::~BruteForceCracker() {

}

nanoseconds BruteForceCracker::crack(std::string pwd, std::chrono::nanoseconds dur) {
	std::string test_pwd = "";
	test_pwd += 32;
	time_point start = high_resolution_clock::now();
	while ((nanoseconds)(high_resolution_clock::now() - start) < dur) {
		if (pwd == this->generate(test_pwd)) {
			return (nanoseconds)(high_resolution_clock::now() - start);
		}
		pwd_plus_one(test_pwd);
	}
	return std::chrono::nanoseconds::max();
}