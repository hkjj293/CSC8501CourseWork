#pragma once
#include <map>
#include <set>
#include<vector>
#include <string>

class Collatz {
public:
	Collatz();
	~Collatz();
	int compute(int input);
	void generate_map(int min, int max);
	void generate_map(std::set<int> num_set);
	void generate_set(int min, int max);
	void generate_string_map();
	std::map<int, int> collatz_map;
	std::map<int, std::vector<int>> rev_collatz_map;
	std::set<int> possible_set;
	std::map<std::string, int> collatz_string_map;
private:
};