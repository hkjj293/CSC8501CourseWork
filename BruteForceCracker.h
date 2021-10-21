#pragma once
#include "Cracker.h"

class BruteForceCracker : public Cracker {
public:
	BruteForceCracker();
	virtual ~BruteForceCracker();
	virtual std::chrono::nanoseconds crack(std::string pwd, std::chrono::nanoseconds dur);
protected:
};