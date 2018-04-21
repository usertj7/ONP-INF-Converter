#include "inf_to_onp.h"

using namespace std;

void inf_to_onp::inputtofile()
{
	fstream plik;
	if (file_or_console) //if data are load from console 
	{
		plik.open("inf_to_onp_form_console_out.txt", ios::out | ios::app);
		if (plik.good())
		{
			plik << "ONP: " << outphrase1 << endl;
			position(3, 3);
			cout << "ONP: " << outphrase1 << endl;
			position(3, 5);
			cout << "THE RESULT HAS BEEN SAVED TO THE FILE. FILE NAME: inf_to_onp_from_console_out.txt " << endl;
			system("pause");
		}
		else exit(0);
	}
	else
	{
		plik.open("inf_to_onp_form_file_out.txt", ios::out | ios::app);
		if (plik.good())
		{
			plik << "ONP: " << outphrase1 << endl;
			position(3, 5);
			cout << "THE RESULT HAS BEEN SAVED TO THE FILE. FILE NAME: inf_to_onp_from_file_out.txt " << endl;
			system("pause");
		}
		else exit(0);
	}
}

void inf_to_onp::deleteothersymbols()
{
	string newphrase = "";
	smatch m;
	regex e("[-=<>\+\*\/\%\^\~\)\(]|[a-z]"); 

	/*
	if ifnds letter or symbol rewrites it to the newphrase and inserts space into a phrase1
	*/
	while (regex_search(phrase1, m, e)) 
	{
		for (unsigned i = 0; i<m.size(); ++i)	
		{
			newphrase += phrase1[m.position(i)];
			phrase1[m.position(i)] = ' ';
		}
	}
	phrase1 = newphrase;
}

int inf_to_onp::check_numbers_of_signs_and_letters()
{
	regex signs("[-=<>\+\*\/\%\^]");
	regex letters("[a-z]");

	auto letters_begin = sregex_iterator(phrase1.begin(), phrase1.end(), letters);
	auto letters_end = sregex_iterator();

	auto signs_begin = sregex_iterator(phrase1.begin(), phrase1.end(), signs);
	auto signs_end = sregex_iterator();
	/*
	if numbers of letters -1 is equal to number of symbols then return 1
	*/
	if (distance(letters_begin, letters_end) - 1 == distance(signs_begin, signs_end)) return 1;
	else return 0;
}

int inf_to_onp::signs_before_equals()
{
	/*
	before symbol '=' cant bo any other symbol
	*/
	string newphrase = phrase1;
	smatch p;
	regex ss("[-<>\+\*\/\%\^~]");
	regex e("[=]");

	int eq_pos = 0;
	int s_pos = 0;

	//find first symbol
	regex_search(newphrase, p, ss);
	for (unsigned i = 0; i < p.size(); ++i) {
		s_pos = p.position(i);
	}
	//find last '='
	while (regex_search(newphrase, p, e))
	{
		for (unsigned i = 0; i < p.size(); ++i) {
			eq_pos = p.position(i);
			newphrase[p.position(i)] = ' ';
		}
	}
	//if there s no any symbol before '=' then return 1
	if (s_pos > eq_pos) return 1;
	else return 0;
}

int inf_to_onp::count_brackets()
{
	regex l_brackett("[\(]");
	regex r_brackett("[\)]");

	auto l_brackett_begin = sregex_iterator(phrase1.begin(), phrase1.end(), l_brackett);
	auto l_brackett_end = sregex_iterator();

	auto r_brackett_begin = sregex_iterator(phrase1.begin(), phrase1.end(), r_brackett);
	auto r_brackett_end = sregex_iterator();

	string s = phrase1;
	smatch b;

	regex el("[\(]");
	regex r("[\)]");

	int l_pos = 0;
	int r_pos = 1;
	/*
	counting the positions of left brackets
	*/
	while (regex_search(s, b, el))
	{
		for (unsigned i = 0; i < b.size(); ++i) {
			l_pos += b.position(i);
			s[b.position(i)] = ' ';
		}
	}
	/*
	counting the positions of right brackets
	*/
	while (regex_search(s, b, r))
	{
		for (unsigned i = 0; i < b.size(); ++i) {
			r_pos += b.position(i);
			s[b.position(i)] = ' ';
		}
	}
	/*
	if the sum of the positions of left brackets is smaller than right brackets 
	and number of left brackets is equal to right brackets then return 1 
	*/
	if (r_pos > l_pos && distance(l_brackett_begin, l_brackett_end) == distance(r_brackett_begin, r_brackett_end)) return 1; //distance function give a numbers of left or right brackets
	else return 0;
}

void inf_to_onp::position(const int x, const int y)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int inf_to_onp::check_other_errors()
{
	smatch m;
	regex two_letters("[a-z]{2,}"); //2 letters next to each other

	smatch ts;
	regex two_signs("[-=<>\+\*\/\%\^]{2,}     [\)][a-z~] "); //2 symbols next to each other

	smatch br;
	regex brackets_next_to_each_other("[\)][/(]|[\(][\)]"); //2 brackets next to each other

	smatch fs;
	regex symbol_on_the_beginning("^[-=<>\+\*\/\%\^\)]"); //symbol at the beginning except negation '~' 

	smatch ns;
	regex symbol_after_negation("[~][-=<>\+\*\/\%\^\)]"); // symbol after negation '~' except left bracket '('

	smatch lnb;
	regex letter_or_negation_after_r_brackett(" [\)][a-z~]"); // letter after right bracket 

	smatch ws;
	regex wrong_signs("[~][-=<>\+\*\/\%\^]"); //symbol after negation  

	smatch ls;
	regex last_signs("[-=<>\+\*\/\%\^\(~]$"); //symbol at the end

	smatch e_b;																				
	regex wrong_sign_in_brackets("[^=][\(][-=<>\+\*\/\%\^\~a-z]{1,}=[-=<>\+\*\/\%\^\~a-z]{1,}[\)]"); //in sequence:  symbol(except equal), left bracket, symbol or letter{one or more time}, equal symbol, ymbol or letter{one or more time}, right bracket
														
	smatch smatch_tab[] = { m, ts,br, fs,ns, lnb, ws, ls, e_b };
	regex regex_tab[] = { two_letters , two_signs , brackets_next_to_each_other, symbol_on_the_beginning, symbol_after_negation, letter_or_negation_after_r_brackett, wrong_signs, last_signs, wrong_sign_in_brackets };
	
	int i = 0, result = 1;
	while ( i< 9)
	{
		if (regex_search(phrase1, smatch_tab[i], regex_tab[i]))
		{
			result = 0; //if result is equal 0 then there s some errors
			break;
		}
		i++;
	}
	return result;
}

void inf_to_onp::clear_file()
{
	fstream plik;
	plik.open("inf_to_onp_form_file_out.txt", ios::out | ios::trunc);
}

void inf_to_onp::correct_file_name()
{
	regex name_end(".txt$");
	smatch ne;
	if (!regex_search(file_name, ne, name_end))
	{
		file_name += ".txt";
	}
}

void inf_to_onp::call_inf_to_onp_from_file()
{
	fstream plik;
	int how_much_expressions;
	file_or_console = 0;
	do {
		
		system("cls");
		position(3, 1);
		cout << "ENTER THE FILE NAME: ";
		cin >> file_name;
		correct_file_name();
		position(3, 3);
		cout << "HOW MUCH EXPRESSIONS DO YOU WANT TO CONVERT: ";
		cin >> how_much_expressions;
		file_or_console = 0;
		plik.open(file_name, ios::in);
		if (plik.good())
		{
			clear_file();
			for (int i = 0; i < how_much_expressions; i++)
			{
				getline(plik, phrase1);
				deleteothersymbols();
				check_form_inf();
				inftoonp();
				inputtofile();
			}
			break;
		}
		else {
			position(3, 5);
			cout << "FILE NAME ERROR!!!" << endl;
			Sleep(3000);
		}
	} while (1);
	
}

void inf_to_onp::check_form_inf()
{
	// if there s no errors then inf_corretnes is equal 1
	if (check_numbers_of_signs_and_letters() && signs_before_equals() && count_brackets() && check_other_errors()) inf_correctness=1;
	else 
	{
		outphrase1 = "error"; inf_correctness=0;
	}
}

void inf_to_onp::input_phrase1()
{
	system("cls");
	position(3,1);
	cout << "ENTER THE PHRASE IN THE INF FORM: ";
	cin >> phrase1;
	file_or_console = 1;
}

void inf_to_onp::inftoonp()
{
	if (inf_correctness==1)
	{
		int prioritets[] = { 0,1,1,2,2,3,3,3,4,5,-1,-1 };
		outphrase1 = "";
		string  q;
		int pos = -2;
		int i = 0;
		while (i < phrase1.length())
		{
			string s = "";
			q = "";
			int j;
			pos = -2;
			for (j = 0; j < operators.length(); j++)   //compare the i-th element of expression with operators
			{
				if (phrase1[i] == operators[j]) {
					pos = j;
					break;
				}
			}
			if (pos != -2) //element of expression is opeerator
			{
				if (stac.empty()) //if stack is empty push the input data on the stack 
				{
					s = "";
					s += phrase1[i];
					stac.push(s);
					prior.push(prioritets[pos]);
				}
				else
				{
					if (phrase1[i] == operators[10])  //if element of expression is left bracket
					{
						s = "";
						s += phrase1[i];
						stac.push(s);
						prior.push(prioritets[pos]);
					}
					else if (phrase1[i] == operators[11])  //if element of expression is right bracket
					{
						do {
							outphrase1 += stac.top();
							stac.pop();
							prior.pop();
						} while (prior.top() != -1);  //pop from the stack untill find the left bracket

						if (prior.top() == -1) //if find left bracket pop them
						{
							prior.pop();
							stac.pop();
						}
						if (i == phrase1.length() - 1)  //if right bracke is the last element of expression pop everything from the stack 
						{
							while (stac.empty() == 0)
							{
								if (stac.top() == "(")
								{
									stac.pop();
									prior.pop();
								}
								else
								{
									outphrase1 += stac.top();
									stac.pop();
									prior.pop();
								}
							}
						}
					}
					else
					{
						if (prior.empty() == 0)  //if stack is not empty
						{
							/*
							if the priority on the top of stack is greater than priority of the input data then pop the element from the stack end get them on the output
							*/
							while (prior.top() >= prioritets[pos]) 
							{
								s = stac.top();
								q += phrase1[i];
								/*
								if on the top of stack is equal input data and it s negation, or equal symbol, or power symbol then push on the stack
								*/
								if (q == s && (phrase1[i] == operators[9] || phrase1[i] == operators[8] || phrase1[i] == operators[0])) break; 
								prior.pop();
								outphrase1 += stac.top();
								stac.pop();
								if (prior.empty()) break;
							}
						}

						//if stack is empty
						s = "";
						s += phrase1[i];
						stac.push(s);
						prior.push(prioritets[pos]);
					}

				}


			}
			/*
			element of expression is letter
			*/
			else 
			{
				outphrase1 += phrase1[i];
				if (i == phrase1.length() - 1)
				{
					while (!stac.empty())
					{
						outphrase1 += stac.top();
						stac.pop();
						prior.pop();
					}
				}
			}
			i++;
		}
	}
}

