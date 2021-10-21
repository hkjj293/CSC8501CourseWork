#include "PwdManager.h"
#include <iostream>

PwdManager::PwdManager() {

}

PwdManager::~PwdManager() {
	
}

std::string PwdManager::generate(std::string input) {
	std::string output = "";
	int offset = 0;
	for (int i = 0; i < input.size(); i++) {
		offset = collatz.compute((input[i] & 255) + offset);
		output += std::to_string(offset);
	}
	return output;
}

void PwdManager::store() {

}

void PwdManager::load() {

}