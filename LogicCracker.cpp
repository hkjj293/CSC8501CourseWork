#include "LogicCracker.h"
#include <vector>
using namespace std::chrono;

LogicCracker::LogicCracker() {
	this->name = "Collatz Logic";
}

LogicCracker::~LogicCracker() {

}

PWD LogicCracker::crack(std::string& pwd, std::chrono::nanoseconds& dur) {
	std::string test_pwd = "";
	for (int i = 0; i < (pwd.size()+4)/4; i++) {
		test_pwd += (char)1;
	}
	PWD cracked = PWD();
	cracked.pwd = "";
	cracked.time = std::chrono::nanoseconds::max();
	time_point start = high_resolution_clock::now();
	while ((nanoseconds)(high_resolution_clock::now() - start) < dur) {
		if (pwd == this->generate(test_pwd)) {
			cracked.pwd = test_pwd;
			cracked.time = (nanoseconds)(high_resolution_clock::now() - start);
			return cracked;
		}
	}
	return cracked;
}