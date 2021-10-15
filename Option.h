#pragma once
#include <string>
#include <functional>

class Option {
public: 
	Option() { title = ""; };
	virtual ~Option(){};
	virtual void print() {};
	virtual void run() = 0;
protected:
	std::string title;
};