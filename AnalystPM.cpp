#include "AnalystPM.h"
#include "PwdGenRule1.h"
#include "PwdGenRule2.h"
#include "BruteForceCracker.h"
#include "LogicCracker.h"
#include <iostream>
#include <memory>
#include <chrono>
#include <mutex>

std::mutex mux;

AnalystPM::AnalystPM() : PwdManager() {
	load();
	this->pwdgens.push_back(new PwdGenRule1());
	this->pwdgens.push_back(new PwdGenRule2());
	this->crackers.push_back(new LogicCracker());
	this->crackers.push_back(new BruteForceCracker());
}

AnalystPM::~AnalystPM() {

}

void AnalystPM::test(int min_char_len, int max_char_len, int num_per_set, std::chrono::nanoseconds dur, std::vector<PWD>& report) {
	int i = min_char_len-1, j = min_char_len/ num_per_set + 1;
	std::chrono::time_point start = std::chrono::high_resolution_clock::now();
	for (auto iter = this->encryted_pwds.begin()+ min_char_len - 1; iter < this->encryted_pwds.end() && iter < this->encryted_pwds.begin() + max_char_len ; iter++) {
		for (auto cr = this->crackers.begin(); cr < this->crackers.end(); cr++) {
			report.push_back((*cr)->crack(*iter, dur));
			i++;
			if (i % num_per_set == 0) {
				mux.lock();
				std::cout << "Processing... Method: " << (*cr)->name << ", set: " << j << "." << std::endl;
				mux.unlock();
				j++;
			}
		}
	}
}

void AnalystPM::print_test(int min_char_len, int max_char_len, int num_per_set, std::chrono::nanoseconds& dur) {
	int j = 1, count = 0, length = max_char_len - min_char_len + 1;
	std::chrono::nanoseconds nano(0);
	int round = 0;
	for (auto cr = this->crackers.begin(); cr < this->crackers.end() ; cr++) {
		std::cout << (*cr)->name << ":" << std::endl;
		int k = 0;
		for (int i = round; i < this->report.size(); i+=2) {
			if (this->report[i].time < dur) {
				nano += this->report[i].time;
				count++;
			}
			k++;
			if (k % num_per_set == 0) {
				std::cout <<  length <<"  Set: " << j << " average: ";
				std::cout << nano.count() / ((long long)(count == 0) + (long long)((count != 0) * (long long)count)) << " Nanoseconds. Crack percentage: " << ((float)count / (float)num_per_set)*100 << "%" << std::endl;
				nano = std::chrono::nanoseconds::zero();
				j++;
				count = 0;
			}
		}
		round++;
	}

}

void AnalystPM::store(std::vector<std::string>& pwds, std::ofstream::openmode mode) {
	std::ofstream ofs;
	try {
		ofs.open("passwordtest.txt", mode);
		for (auto iter = this->encryted_pwds.begin(); iter < this->encryted_pwds.end(); iter++) {
			ofs << *iter << std::endl;
		}
	}
	catch (const std::ofstream::failure& e) {
		std::cout << e.what() << std::endl;
	}
	ofs.close();

}

inline void AnalystPM::store() {
	this->store(this->encryted_pwds, std::ofstream::trunc);
}

void AnalystPM::load() {
	std::ifstream ifs;
	try {		
		ifs.open("passwordtest.txt");
		if (ifs.is_open()) {
			std::string pwd;
			while (ifs.good() && !ifs.eof()) {
				ifs >> pwd;
				this->encryted_pwds.push_back(std::move(pwd));
			}
		}
	}
	catch (const std::ifstream::failure& e) {
		std::cout << e.what() << std::endl;
	}
	ifs.close();
}

void AnalystPM::gen_rand_pwd(int min_char_len, int max_char_len, int num_per_set) {
	this->encryted_pwds.clear();
	for (int i = 0; i < this->pwdgens.size(); i++) {
		this->pwdgens[i]->reset_char_bank();
		for (int j = min_char_len; j <= max_char_len; j++) {
			for (int k = 0; k < num_per_set; k++) {
				this->encryted_pwds.push_back(this->generate(this->pwdgens[i]->generate(j)));
			}
			std::cout << "Method: " << i << ", set: " << j << " generated." << std::endl;
		}
	}
}

