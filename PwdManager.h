#pragma once
#include <string>
#include "Collatz.h"

class PwdManager {
public:
	PwdManager();
	virtual ~PwdManager();
	std::string generate(std::string input);
	virtual void store();
	virtual void load();

protected:
	Collatz collatz;
};