#pragma once
#include <vector>
#include <fstream>
#include "PwdManager.h"
#include "PwdGen.h"
#include "Cracker.h"

class AnalystPM : public PwdManager {
public:
	AnalystPM();
	virtual ~AnalystPM();
	void gen_rand_pwd(int min_char_len, int max_char_len, int per_set);
	void store(std::vector<std::string>& pwds, std::ifstream::openmode mode);
	void test(int min_char_len, int max_char_len, int num_per_set, std::chrono::nanoseconds dur);
	virtual inline void store();
	virtual void load();
private:
	std::vector<std::string> encryted_pwds;
	std::vector<PwdGen*> pwdgens;
	std::vector<Cracker*> crackers;
};