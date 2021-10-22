#include "AuthPM.h"

AuthPM::AuthPM() : PwdManager(), users(new BST<User>()) {
	load();
}

AuthPM::~AuthPM() {
	if (this->users != NULL) {
		delete users;
		users = NULL;
	}
}

void AuthPM::create(std::string name, std::string pwd) {
	User user(name, this->generate(pwd));
	std::vector<User> usrs = { user };
	if (!this->users->has_element(user)) {
		this->users->add_node(user);
		this->store(std::move(usrs), std::ifstream::app);
		std::cout << "Add user success!" << std::endl;
	}
	else {
		std::cout << "Add user failure!" << std::endl;
	}
}

int AuthPM::auth(std::string name, std::string pwd) {
	User user(name, this->generate(pwd));
	if (this->users->has_element(user)) {
		bool match = false;
		std::function<void(User&)> fn = [this, &match, &pwd](User& usr) {if (usr.encryped_pwd == this->generate(pwd)) { match = true; }};
		this->users->iterate(&fn);
		if (match) {
			std::cout << "Success!" << std::endl;
			return 1;
		}
		std::cout << "Failure!" << std::endl;
		return 0;
	}
	std::cout << "Failure!" << std::endl;
	return 2;
}

void AuthPM::store(std::vector<User>&& usr, std::ofstream::openmode mode) {
	std::ofstream ofs;
	try {
		ofs.open("password.txt", mode);
		for(auto iter = usr.begin() ; iter < usr.end() ; iter++)
		ofs << iter->name << " " << iter->encryped_pwd <<std::endl;
	}
	catch (const std::ofstream::failure& e) {
		std::cout << e.what() << std::endl;
	}
	ofs.close();
	
}

void AuthPM::store() {
	std::vector<User> usrs;
	std::function<void(User&)> get = [&usrs](User& usr) {usrs.push_back(usr); };
	this->users->iterate(&get);
	this->store(move(usrs), std::ofstream::trunc);
}

void AuthPM::load() {
	std::ifstream ifs;
	try {		
		ifs.open("password.txt");
		if (ifs.is_open()) {
			std::string name, pwd;
			while (ifs.good() && !ifs.eof()) {
				ifs >> name >> pwd;
				User usr(std::move(name), std::move(pwd));
				if (name != "" && pwd != "" && !this->users->has_element(usr)) {
					this->users->add_node(usr);
				}
			}
		}
	}
	catch (const std::ifstream::failure& e) {
		std::cout << e.what() << std::endl;
	}
	ifs.close();
}