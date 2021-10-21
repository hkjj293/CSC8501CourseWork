#pragma once
#include <map>
#include <set>
#include<vector>

class Collatz {
public:
	Collatz();
	~Collatz();
	int compute(int input);
	void generate_map(int min, int max);
	void generate_map(std::set<int> num_set);
	std::map<int, int> collatz_map;
	std::map<int, std::vector<int>> rev_collatz_map;
private:
};