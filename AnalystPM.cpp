#include "AnalystPM.h"
#include "PwdGenRule1.h"
#include "PwdGenRule2.h"
#include "BruteForceCracker.h"
#include <iostream>
#include <memory>
#include <chrono>

AnalystPM::AnalystPM() : PwdManager() {
	load();
	this->pwdgens.push_back(new PwdGenRule1());
	this->pwdgens.push_back(new PwdGenRule2());
	this->crackers.push_back(new BruteForceCracker());
}

AnalystPM::~AnalystPM() {

}

void AnalystPM::test(int min_char_len, int max_char_len, int num_per_set, std::chrono::nanoseconds dur) {
	int i = 0, j = 1, count = 0, length = max_char_len - min_char_len + 1;
	std::chrono::time_point start = std::chrono::high_resolution_clock::now();
	this->report.reset(new std::vector<PWD>());
	for (auto cr = this->crackers.begin(); cr < this->crackers.end(); cr++) {
		for (auto iter = this->encryted_pwds.begin(); iter < this->encryted_pwds.begin() + length; iter++) {
			this->report->push_back((*cr)->crack(*iter,dur));
			i++;
			if (i % num_per_set == 0) {
				std::cout << "Processing... Method: " << (*cr)->name << ", set: " << j << "." << std::endl;
				j++;
			}
		}
	}
	std::cout << (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start)).count() << std::endl;
	this->print_test(min_char_len, max_char_len, num_per_set, dur);
}

void AnalystPM::print_test(int min_char_len, int max_char_len, int num_per_set, std::chrono::nanoseconds& dur) {
	int i = 0, j = 1, count = 0, length = max_char_len - min_char_len + 1;
	std::chrono::nanoseconds nano(0);
	for (auto cr = this->crackers.begin(); cr < this->crackers.end(); cr++) {
		std::cout << (*cr)->name << ":" << std::endl;
		for (auto iter = this->encryted_pwds.begin(); iter < this->encryted_pwds.begin() + length; iter++) {
			if (this->report->at(i).time < dur) {
				std::cout << this->report->at(i).time.count() << " - " << dur.count() << std::endl;
				nano += (*this->report)[i].time;
				count++;
			}
			i++;
			if (i % num_per_set == 0) {
				std::cout << "  Set: " << j << " average: ";
				std::cout << nano.count() / ((long long)(count == 0) + (long long)((count != 0) * (long long)count)) << " Nanoseconds. Crack percentage: " << ((float)count / (float)num_per_set)*100 << "%" << std::endl;
				nano = std::chrono::nanoseconds::zero();
				j++;
				count = 0;
			}
		}
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

