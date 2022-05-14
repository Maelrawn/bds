#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>
#include <string>
#include <cctype>
#include <stdio.h>
#include <curses.h>
#include <regex>
#include "./customer.hpp"
#include "curses.cpp"

int main(int argv, char** argc){
	if(argv != 3){
		printf("Run with two file locations as arguments.\n");
		return 1;
	}
};