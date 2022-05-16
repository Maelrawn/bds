#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>
#include <string>
#include <cctype>
#include <stdio.h>
#include <curses.h>
#include <cmath>
#include <regex>
#include <unistd.h>
#include "./customer.cpp"
#include "./curses.cpp"

int main(int argv, char** argc){
	if(argv != 3){
		printf("Run with two file locations as arguments.\n");
		return 1;
	}
	string customerFile = argc[1];
	string purchaseFile = argc[2];
	vector<AllCustomers*> AllCustomers 
		= populate_customers_from_file(customerFile, purchaseFile);
	// for(int i = 0; i < AllCustomers.size(); i++){
	// 	cout<<AllCustomers.at(i)->get_firstn()<<'\n';
	// 	for(int j = 0; j < AllCustomers.at(i)->get_purchases().size(); j++){
	// 		cout<<AllCustomers.at(i)->get_purchases().at(j)->get_item()<<'\n';
	// 	}
	// }
	init_curses();
	//intro_graphic();
	main_menu(AllCustomers);
	endwin();
	curs_set(2);
};






