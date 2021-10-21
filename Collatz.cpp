#include "Collatz.h"
#include <iostream>

Collatz::Collatz() {}

Collatz::~Collatz() {}

int Collatz::compute(int num) {
	int count = 0;
	while (num != 1) {
		//std::cout << num << std::endl;
		num = ((num & 1) * (num*3 + 1)) + ((!(num & 1)) * (num >> 1));
		count++;
	}
	return count;
}

void Collatz::generate_map(int min, int max) {
	//collatz_map.emplace();
}

void Collatz::generate_map(std::set<int> num_set) {

}