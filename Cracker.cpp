#pragma once
#include "Cracker.h"

std::string Cracker::generate(std::string input) {
	std::string output = "";
	int offset = 0;
	for (int i = 0; i < input.size(); i++) {
		offset = collatz.compute((input[i] & 255) + offset);
		output += std::to_string(offset);
	}
}