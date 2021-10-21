#pragma once
#include "PwdGen.h"
#include <set>

class PwdGenRule2 : public PwdGen{
public:
	PwdGenRule2();
	virtual ~PwdGenRule2();
	virtual inline std::string generate(int length);
};