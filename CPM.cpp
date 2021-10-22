#include<iostream>
#include "CPM.h"
#include <thread>
#include  <any>
#include <fstream>

void run_in_thread(AnalystPM& apm, int from, int to, int size, std::chrono::nanoseconds dur, std::vector<PWD>& report) {
	apm.test(from, to, size, dur,report);
}

CPM::CPM() {
	this->running = true;
	menu_init();
}

CPM::~CPM() {

}

void CPM::init() {

}

void CPM::loop() {
	while (this->running) {
		std::cout << std::endl;
		menu.show();
		switch (menu.curr_option) {
		case 1:
			create_pwd();
			break;
		case 2:
			auth_pwd();
			break;
		case 3:
			gen_file();
			break;
		case 4:
			analyse_file();
			break;
		case 5:
			decrypt();
			break;
		case 6:
			this->running = false;
		}
		menu.curr_option = 0;
	}
}

void CPM::start() {
	init();
	loop();
}

void CPM::stop() {
	this->running = false;
}

void CPM::menu_init() {
	menu.banner.push_back("++========================================================++");
	menu.banner.push_back("++                 Collatz Password Manager               ++");
	menu.banner.push_back("++========================================================++");
	menu.options.push_back("  1. Create username/password");
	menu.options.push_back("  2. Check username and password");
	menu.options.push_back("  3. Generate password strength analysis file");
	menu.options.push_back("  4. Analys password strength analysis file");
	menu.options.push_back("  5. Decrypt an encrypted password");
	menu.options.push_back("  6. Exit");
}

void CPM::create_pwd() {
	std::string name, pwd;
	std::cout << "Input a new username: ";
	std::getline(std::cin, name);
	std::cout << "Input a new password: ";
	std::getline(std::cin, pwd);
	this->auth_pm.create(name, pwd);
}

void CPM::auth_pwd() {
	std::string name, pwd;
	int i = 3;
	std::cout << "Input your username: ";
	std::getline(std::cin, name);
	while (i > 0) {
		std::cout << "Input your password (You have " << i-- << " times left.): ";
		std::getline(std::cin, pwd);
		if (this->auth_pm.auth(name, pwd) > 0) { break; }
	}
}

void CPM::gen_file() {
	this->analyst_pm.gen_rand_pwd(1,100,100);
	this->analyst_pm.store();
}

void CPM::analyse_file() {
	this->analyst_pm.report.clear();
	std::chrono::nanoseconds dur = (std::chrono::nanoseconds)std::chrono::milliseconds(10);
	std::vector<std::thread> threads;
	int limit = 2000, num_per_batch = 100, batch_size = 100, num_thread = std::thread::hardware_concurrency()/2;
	int left = limit;
	std::vector<std::vector<PWD>> reports(num_thread);
	batch_size = (left / num_per_batch) / (num_thread);
	for (int i = 0; i < num_thread; i++) {
		threads.push_back(std::thread(run_in_thread, std::ref(this->analyst_pm), i * num_per_batch * batch_size + 1, (i + 1) * num_per_batch * batch_size, num_per_batch, dur, std::ref(reports[i])));
		left -= num_per_batch * batch_size;
	}
	for (int i = 0; i < num_thread; i++) {
		threads[i].join();
	}
	for (int i = 0; i < num_thread; i++) {
		std::ofstream ofs;
		try {
			ofs.open("reoprt.txt", std::ofstream::app);
			for (auto iter = reports[i].begin(); iter < reports[i].end(); iter++) {
				ofs << (*iter).time.count() << std::endl;
			}
		}
		catch (const std::ofstream::failure& e) {
			std::cout << e.what() << std::endl;
		}
		ofs.close();
		this->analyst_pm.report.insert(this->analyst_pm.report.end(), reports[i].begin(), reports[i].end());
	}
	for (int i = 0; i < left/num_per_batch; i++) {
		reports[i].clear();
		threads[i] = std::thread(run_in_thread, std::ref(this->analyst_pm), (limit - left) + i * num_per_batch + 1, (limit - left) + (i+1) * num_per_batch, num_per_batch, dur, std::ref(reports[i]));
	}
	for (int i = 0; i < left/num_per_batch; i++) {
		threads[i].join();
	}
	for (int i = 0; i < left/num_per_batch; i++) {
		this->analyst_pm.report.insert(this->analyst_pm.report.end(), reports[i].begin(), reports[i].end());
	}
	this->analyst_pm.print_test(1, limit , num_per_batch, dur);
}

void CPM::decrypt() {
	this->analyst_pm.gen_rand_pwd(1, 100, 100);
	this->analyst_pm.store();
}

