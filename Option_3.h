#pragma once
#include "Option.h"

class Option_3 : public Option {
public:
	Option_3() : Option() {};
	virtual ~Option_3() {};
	virtual void print();
	virtual void run();
};