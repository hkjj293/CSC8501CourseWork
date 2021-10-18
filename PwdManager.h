#pragma once
#include <string>
#include "Collatz.h"
#include "FileManager.h"

class PwdManager {
public:
	PwdManager();
	~PwdManager();
	std::string generate(std::string input);
	void store();

protected:
	Collatz collatz;
	std::vector<FileManager*> file_manager;
};