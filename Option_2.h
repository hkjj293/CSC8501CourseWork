#pragma once
#include "Option.h"

class Option_2 : public Option {
public:
	Option_2() : Option() {};
	virtual ~Option_2() {};
	virtual void print();
	virtual void run();
};