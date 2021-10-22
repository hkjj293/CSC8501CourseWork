#include "BruteForceCracker.h"
#include <vector>
using namespace std::chrono;

inline void pwd_plus_one(std::string& pwd, char start) {
	pwd[0]++;
	for (int i = 0; i < pwd.size() - 1; i++) {
		if (pwd[i] == 0) {
			pwd[i] = start;
			pwd[i + 1]++;
		}
	}
	if (pwd[pwd.size() - 1] == 0) {
		pwd[pwd.size() - 1] = start;
		pwd.push_back(start);
	}	
}

BruteForceCracker::BruteForceCracker() {
	this->name = "Brute Force";
}

BruteForceCracker::~BruteForceCracker() {

}

PWD BruteForceCracker::crack(std::string& pwd, std::chrono::nanoseconds& dur) {
	std::string test_pwd((size_t)((pwd.size()-1) / 3) + 1,1);
	PWD cracked = PWD();
	cracked.pwd = "";
	cracked.time = std::chrono::nanoseconds::max();
	time_point start = high_resolution_clock::now();
	while ((nanoseconds)(high_resolution_clock::now() - start) < dur && pwd != this->generate(test_pwd)) {
		pwd_plus_one(test_pwd,1);
	}
	cracked.time = (nanoseconds)(high_resolution_clock::now() - start);
	//if(this->generate(test_pwd) == pwd)std::cout << this->generate(test_pwd) << " - " << pwd << std::endl;
	cracked.pwd = test_pwd;
	return cracked;
} 