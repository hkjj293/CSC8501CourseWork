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
	std::unique_ptr<std::vector<std::string>> report(new std::vector<std::string>());
	for (auto iter = this->crackers.begin(); iter < this->crackers.end(); iter++) {
		for (auto pws = this->encryted_pwds.begin(); pws < this->encryted_pwds.end(); pws++) {
			report->push_back(((*iter)->crack(*pws,dur)));
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
		for (int j = min_char_len; j <= max_char_len; j++) {
			for (int k = 0; k < num_per_set; k++) {
				this->encryted_pwds.push_back(this->generate(this->pwdgens[i]->generate(j)));
			}
			std::cout << "Difficulty: " << i << ", set: " << j << " generated." << std::endl;
		}
	}
}

