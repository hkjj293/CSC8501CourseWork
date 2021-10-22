#include "LogicCracker.h"
#include <vector>
#include <chrono>
#include <mutex>
using namespace std::chrono;

std::mutex muxi;

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
	PWD cracked = PWD();
	cracked.pwd = "";
	cracked.time = std::chrono::nanoseconds::max();
	time_point start_time = high_resolution_clock::now();
	while ((nanoseconds)(high_resolution_clock::now() - start_time) < dur && labels[labels.size() - 1] <= (int)pwd.size()) {
		accum = "";
		for (int j = labels[labels.size() - 2]; j < labels[labels.size() - 1]; j++) {
			accum += pwd[j];
		}
		std::vector<int> v = this->collatz.rev_collatz_map[this->collatz.collatz_string_map[accum]];
		if (v.size() > 1 || v[0] > 0) {
			offset.push_back(this->collatz.collatz_string_map[accum]);
			labels.push_back(labels[labels.size() - 1] + 1);
		}
		else {
			if (accum.size() > 2) {
				labels.pop_back();
				offset.pop_back();
			}
			labels[labels.size() - 1]++;			
		}
	}
	labels.pop_back();
	for (int j = 0 ; j < labels.size()-1 ; j++){
		accum = "";
		//std::cout << labels[j] << " -[" << j << " ]-" << labels[j + 1] << " - ";
		for (int i = labels[j]; i < labels[j+1]; i++) {
			//std::cout << accum << " " ;
			accum += (pwd[i]);
		}
		for (int i = 0; i < this->collatz.rev_collatz_map[this->collatz.collatz_string_map[accum]].size(); i++) {
			int diff = this->collatz.rev_collatz_map[this->collatz.collatz_string_map[accum]][i] - offset[j];
			if (diff > 0 && diff < 256) {
				test_pwd += this->collatz.rev_collatz_map[this->collatz.collatz_string_map[accum]][i] - offset[j];
			}
		}
		//test_pwd += this->collatz.rev_collatz_map[this->collatz.collatz_string_map[accum]][0]-offset[j];
	}
	/*/
	muxi.lock();
	std::cout << test_pwd << " & " << this->generate(test_pwd) << " - " << pwd << std::endl;
	muxi.unlock();
	/*
	muxi.lock();
	std::cout << this->generate(test_pwd) << " - " << pwd << std::endl;
	std::cout << (this->generate(test_pwd) == pwd) << std::endl;
	muxi.unlock();
	*/
	cracked.time = (nanoseconds)(high_resolution_clock::now() - start_time);
	if (this->generate(test_pwd) != pwd) cracked.time = nanoseconds::max();
	cracked.pwd = test_pwd;
	return cracked;
}