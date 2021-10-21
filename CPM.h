#pragma once
#include "Menu.h"
#include "AuthPM.h"
#include "AnalystPM.h"

class CPM {
public:
	CPM();
	~CPM();
	void start();
	void stop();
private:
	void init();
	void loop();
	void menu_init();
	void create_pwd();
	void auth_pwd();
	void gen_file();
	void analyse_file();
	bool running;
	Menu menu;
	AuthPM auth_pm;
	AnalystPM analyst_pm;
};