#ifndef INF_TO_ONP_H
#define INF_TO_ONP_H
#include <stack>
#include <iostream>
#include<string>
#include<fstream>
#include <windows.h>
#include <regex>
#include <iterator>
#include "onp_to_inf.h"
using namespace std;

class inf_to_onp {
	friend class onp_to_inf;
private:

	stack<std::string>stac;
	stack<int>prior;
	string phrase1;
	string outphrase1;
	string operators = "=<>+-*/%^~()";
	string file_name;
	bool inf_correctness;
	bool file_or_console;

public:
	/*
	function converts from ONP to INF
	*/
	void inftoonp();
	/*
	function enters data into a file
	*/
	void inputtofile();
	/*
	nction removes characters that are not letters, operators or brackets
	*/
	void deleteothersymbols();
	/*
	file cleaner
	*/
	void clear_file();
	/*
	starting the conversion procedure if the data is loaded from a file
	*/
	void call_inf_to_onp_from_file();
	/*
	function that checks correctness of the inf expression
	*/
	void check_form_inf();
	/*
	function that gets the data from console 
	*/
	void input_phrase1();
	//----------------------
	/*
	functions that search for errors
	*/
	int check_other_errors();
	int check_numbers_of_signs_and_letters();
	int signs_before_equals();
	int count_brackets();
	//------------------------
	/*
	function that sets the cursor to x y position
	*/
	void position(const int x, const int y);
	/*
	fumction check correct of file`s name
	*/
	void correct_file_name();
};


#endif
