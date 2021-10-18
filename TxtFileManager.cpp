#pragma once
#include "TxtFileManager.h"

void TxtFileManager::write() {
	std::ofstream out_file;
	out_file.open(this->file_name + "txt");

	out_file.close();

}

std::string TxtFileManager::read() {
	return "";
}