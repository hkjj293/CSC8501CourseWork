#pragma once
#include <map>
#include <set>

class Collatz {
public:
	Collatz();
	~Collatz();
	int compute(int input);
	void generate_map(int min, int max);
	void generate_map(std::set<int> num_set);
private:
	std::map<int, int> collatz_map;
};