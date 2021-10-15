#pragma once
#include "Option.h"

class Option_1 : public Option {
public:
	Option_1() : Option() {};
	virtual ~Option_1() {};
	virtual void print();
	virtual void run();
};