#pragma once
#include <string>
#include "Collatz.h"

class PwdManager {
public:
	PwdManager();
	~PwdManager();
	std::string generate(std::string input);
private:
	Collatz collatz;
	FileManager file_manager;
};