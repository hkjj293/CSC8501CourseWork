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
	void menu_init();
	void create_pwd();
	void auth_pwd();
	void gen_report();
	void analyse_report();
	bool running;
	Menu menu;
	AuthPM auth_pm;
	AnalystPM analyst_pm;
};