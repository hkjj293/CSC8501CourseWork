#pragma once
#include "FileManager.h"

class TxtFileManager : FileManager {
public:
	TxtFileManager() : FileManager() {};
	TxtFileManager(std::string filename) : FileManager(filename) {};
	virtual ~TxtFileManager() {};
	virtual void write();
	virtual std::string read();
};