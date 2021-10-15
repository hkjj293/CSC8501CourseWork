#pragma once
#include "Option.h"
#include <vector>
class Menu {
public:
	Menu();
	~Menu();
	void print();
	void choose_option();
private:
	void set_banner();
	void set_options();
	std::vector<std::string> banner;
	std::vector<Option*> options;
};