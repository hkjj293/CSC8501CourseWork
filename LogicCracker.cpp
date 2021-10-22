#include "LogicCracker.h"
#include <vector>
#include <chrono>
using namespace std::chrono;

LogicCracker::LogicCracker() {
	this->name = "Collatz Logic";
	this->collatz.generate_set(1,255);
	this->collatz.generate_map(this->collatz.possible_set);
	this->collatz.generate_string_map();
}

LogicCracker::~LogicCracker() {

}

PWD LogicCracker::crack(std::string& pwd, std::chrono::nanoseconds& dur) {
	std::string accum = "";
	std::string test_pwd = "";
	std::vector<int> labels = {0,1};
	std::vector<int> offset = { 0 };
	std::vector<int> trial_pos = { 0 };
	PWD cracked = PWD();
	cracked.pwd = "";
	cracked.time = std::chrono::nanoseconds::max();
	time_point start_time = high_resolution_clock::now();
	while ((nanoseconds)(high_resolution_clock::now() - start_time) < dur && labels[labels.size() - 1] <= pwd.size()) {
		accum.assign(pwd.begin() + labels[labels.size()-2], pwd.begin() + labels[labels.size() - 1] -1);
		std::vector<int> v = this->collatz.rev_collatz_map[this->collatz.collatz_string_map[accum]];
		if (v.size() > 0) {
			offset.push_back(this->collatz.collatz_string_map[accum]);
			labels.push_back(labels[labels.size() - 1] + 1);
		}
		else {
			if (accum.size() > 2) {
				labels.pop_back();
			}
			labels[labels.size() - 1]++;			
		}

	}
	labels.pop_back();
	for (auto iter = labels.begin(); iter < labels.end()-1; iter++) {
		accum.assign(pwd.begin() + (*iter), pwd.begin() + *(iter));
		test_pwd += (char)(this->collatz.collatz_string_map[accum] - offset[(*iter)]);
	}
	//std::cout << this->generate(test_pwd) << " - " << pwd << std::endl;
	std::cout << (this->generate(test_pwd) == pwd) << std::endl;
	//std::cout << std::endl;
	cracked.time = (nanoseconds)(high_resolution_clock::now() - start_time);
	cracked.pwd = test_pwd;
	return cracked;
}