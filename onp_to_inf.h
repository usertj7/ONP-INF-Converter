#ifndef ONP_TO_INF_H
#define ONP_TO_INF_H
#include <stack>
#include <iostream>
#include<string>
#include<fstream>
#include <windows.h>
#include "inf_to_onp.h"

using namespace std;

class onp_to_inf {
	friend class inf_to_onp;
private:
	
	std::stack<std::string>sta;
	std::stack<int>prio;
	std::string phrase;
	std::string outphrase;
	std::string operators = "=<>+-*/%^~";
	std::string letters = "aeiouyqwrtpsdfghjklzxcvbnm";
	size_t position;
	string file__name;
	bool onp_correctness;
	bool file_or_console;
	
public:
	/*
	function converts from  INF to ONP 
	*/
	void onptoinf();
	/*
	function that checks correctness of the onp expression
	*/
	void checkformonp();
	/*
	function enters data into a file
	*/
	void inputtofile();
	/*
	function that gets the data from console
	*/
	void input_phrase();
	/*
	starting the conversion procedure if the data is loaded from a file
	*/
	void call_onp_to_inf_from_file();
	/*
	file cleaner
	*/
	void clear_file();
	/*
	function that sets the cursor to x y position
	*/
	void position1(const int x, const int y);
	/*
	fumction check correct of file`s name
	*/
	void correct_file_name();
};

#endif
