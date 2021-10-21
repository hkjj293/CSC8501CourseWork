#pragma once
#include "PwdGen.h"

class PwdGenRule1 : public PwdGen {
public:
	PwdGenRule1();
	virtual ~PwdGenRule1();
	virtual inline void reset_char_bank();
	void inline reset_char_set();
	virtual inline std::string generate(int length);
private:
	std::vector<char> char_set;
};