#include "Collatz.h"
#include <iostream>
#include <functional>

Collatz::Collatz() {}

Collatz::~Collatz() {}

int Collatz::compute(int num) {
	if (this->collatz_map[num] != 0) { return this->collatz_map[num]; }
	//std::cout << num << std::endl;
	int count = 0;
	int fix_num = num;
	while (num > 1) {
		num = ((num & 1) * (num*3 + 1)) + ((!(num & 1)) * (num >> 1));
		count++;
	}
	this->collatz_map[fix_num] = count;
	return count;
}

void Collatz::generate_map(int min, int max) {
	collatz_map.clear();
	rev_collatz_map.clear();
	for (int i = min; i <= max; i++) {
		this->collatz_map[i] = this->compute(i);
	}
	int count = 1;
	for (auto iter = this->collatz_map.begin(); iter != this->collatz_map.end(); iter++) {
		this->rev_collatz_map[(*iter).second].push_back((*iter).first);
	}

}

void Collatz::generate_map(std::set<int> num_set) {
	collatz_map.clear();
	rev_collatz_map.clear();
	for (auto iter = num_set.begin(); iter != num_set.end(); iter++){
		this->collatz_map[*iter] = this->compute(*iter);
	}
	for (auto iter = this->collatz_map.begin(); iter != this->collatz_map.end(); iter++) {
		this->rev_collatz_map[(*iter).second].push_back((*iter).first);
	}
}

void Collatz::generate_set(int min, int max) {
	this->possible_set.clear();
	generate_map(min, max);
	for (auto iter = this->collatz_map.begin(); iter != this->collatz_map.end(); iter++) {
		this->possible_set.insert((*iter).first);
		this->possible_set.insert((*iter).second);
	}
	int last = 0;
	while (last < this->possible_set.size()) {
		last = this->possible_set.size();
		for (auto iter = this->possible_set.begin(); iter != this->possible_set.end(); iter++) {
			for (auto in = this->possible_set.begin(); in != this->possible_set.end(); in++) {
				this->possible_set.insert(compute(*iter + *in));
			}
		}
	}
}

void Collatz::generate_string_map() {
	for (auto iter = this->collatz_map.begin(); iter != this->collatz_map.end(); iter++) {
		//std::cout << std::to_string((*iter).second) << "][][][][][][][][";
		this->collatz_string_map[std::to_string((*iter).second)] = (*iter).second;
	}
}