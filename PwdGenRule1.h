#pragma once
#include "PwdGen.h"

class PwdGenRule1 : public PwdGen {
public:
	PwdGenRule1();
	virtual ~PwdGenRule1();
	virtual inline std::string generate(int length);
};