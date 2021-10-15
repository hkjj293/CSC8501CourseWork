#include<iostream>
#include "CPM.h"

void display_menu();

int main() {
	//CPM* cpm = new CPM();
	Menu* menu = new Menu();
	menu->print();
	menu->choose_option();
}
