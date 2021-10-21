#pragma once
#include "Cracker.h"

class LogicCracker : public Cracker {
public:
	LogicCracker();
	virtual ~LogicCracker();
	virtual PWD crack(std::string& pwd, std::chrono::nanoseconds& dur);
protected:
};