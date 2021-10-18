#pragma once
#include <string>
#include <fstream>
#include <vector>

class FileManager {
public:
	FileManager() : file_name("default"){};
	FileManager(std::string filename) : file_name(filename) {};
	~FileManager() {};
	virtual void write() = 0;
	virtual std::string read() = 0;
	std::string file_name;
	std::vector<std::string> buff;
protected:
	
};