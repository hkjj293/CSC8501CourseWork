#pragma once
#include <vector>
#include <string>
#include <string>
#include <vector>

class Menu {
public:
	Menu();
	~Menu();
	void show();
	int curr_option;
	std::vector<std::string> banner, options;
private:
	int get_input();
};