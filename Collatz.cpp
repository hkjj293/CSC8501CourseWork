#include "Collatz.h"
#include <iostream>

Collatz::Collatz() {}

Collatz::~Collatz() {}

int Collatz::compute(int num) {
	if (this->collatz_map[num] != 0) { return this->collatz_map[num]; }
	//std::cout << num << std::endl;
	int count = 0;
	int fix_num = num;
	while (num != 1) {
		num = ((num & 1) * (num*3 + 1)) + ((!(num & 1)) * (num >> 1));
		count++;
	}
	this->collatz_map[fix_num] = count;
	return count;
}

void Collatz::generate_map(int min, int max) {
	for (int i = min; i <= max; i++) {
		this->collatz_map[i] = this->compute(i);
	}
}

void Collatz::generate_map(std::set<int> num_set) {
	for (auto iter = num_set.begin(); iter != num_set.end(); iter++)
	{
		this->collatz_map[*iter] = this->compute(*iter);
	}
}