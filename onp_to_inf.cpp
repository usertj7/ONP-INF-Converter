#include "onp_to_inf.h"

using namespace std;

void onp_to_inf::inputtofile()
{ 
	fstream plik;
	if (file_or_console)
	{
		plik.open("onp_to_inf_form_console_out.txt", ios::out | ios::app);
		if (plik.good())
		{
			plik << "INF: " << outphrase << endl;
			position1(3, 3);
			cout << "INF: " << outphrase << endl;
			position1(3, 5);
			cout << "THE RESULT HAS BEEN SAVED TO THE FILE. FILE NAME: onp_to_inf_from_console_out.txt " << endl;
			system("pause");
		}
		else exit(0);
	}
	else
	{
		plik.open("onp_to_inf_form_file_out.txt", ios::out | ios::app);
		if (plik.good())
		{
			plik << "INF: " << outphrase << endl;	
		}
		else exit(0);
	}
	
}

void onp_to_inf::input_phrase()
{
	system("cls");
	position1(3, 1);
	cout << "ENTER THE PHRASE IN THE ONP FORM: ";
	cin >> phrase;
	file_or_console = 1;
}

void onp_to_inf::correct_file_name()
{
	regex name_end(".txt$");
	smatch ne;
	if (!regex_search(file__name, ne, name_end))
	{
		file__name += ".txt";
	}
}

void onp_to_inf::call_onp_to_inf_from_file()
{
	
	fstream plik;
	int how_much_expressions;
	
	do{
		
		system("cls");
		position1(3, 1);
		cout << "ENTER THE FILE NAME: ";
		cin >> file__name;
		correct_file_name();
		position1(3, 3);
		cout << "HOW MUCH EXPRESSIONS DO YOU WANT TO CONVERT: ";
		cin >> how_much_expressions;
		file_or_console = 0;
		plik.open(file__name, ios::in);
		if (plik.good())
		{
			clear_file();
			for (int i = 0; i < how_much_expressions; i++)
			{
				getline(plik, phrase);
				checkformonp();
				onptoinf();
				inputtofile();
			}
			position1(3, 5);
			cout << "THE RESULT HAS BEEN SAVED TO THE FILE. FILE NAME: onp_to_inf_from_file_out.txt " << endl;
			system("pause");
			break;
		}
		else {
			position1(3, 5);
			cout << "FILE NAME ERROR!!!" << endl;
			Sleep(3000);
		}
	} while (1);
	
	
	 
}

void onp_to_inf::clear_file()
{
	fstream plik;
	plik.open("onp_to_inf_form_file_out.txt", ios::out | ios::trunc);
}

void onp_to_inf::position1(const int x, const int y)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
 
void onp_to_inf::onptoinf()
{
	if (onp_correctness == 1)
	{
		int prioritets[] = { 0,1,1,2,2,3,3,3,4,5 };
		string t = "";
		string temp;

		for (int i = 0; i < phrase.length(); i++)
		{
			int j;
			int pos = -1;

			if (phrase[i] == ' ') continue;

			for (j = 0; j < 10; j++)
			{
				if (phrase[i] == operators[j]) //compare the i-th element of expression with operators
				{
					pos = j;
					break;
				}
			}

			if (pos != -1)   //element of the expression is operator
			{
				if (pos == 9) //if the element of expression is negation
				{
					temp = phrase[i];
					temp += sta.top();
					sta.pop();
					int pr = prio.top();
					prio.pop();
					/*
					if the priority on the stack is greater than priority of the output element and the neagtino in on the stack 
					*/
					if (pr <= prioritets[pos] && temp[0] != '~')  
					{
						temp = "(" + temp + ")";
					}
					sta.push(temp);
					prio.push(prioritets[pos]);
				}
				else	//if the element of expression is any symbol except negation 
				{
					temp = sta.top();
					sta.pop();
					int pr = prio.top();
					prio.pop();
					if (pr <= prioritets[pos])
					{
						temp = "(" + temp + ")";
					}

					outphrase = sta.top();
					sta.pop();
					pr = prio.top();
					prio.pop();
					if (pr < prioritets[pos])
					{
						outphrase = "(" + outphrase + ")";
					}


					outphrase += phrase[i];
					outphrase += temp;

					sta.push(outphrase);
					prio.push(prioritets[pos]);
				}
			}
			else  //if the element of expression is letter
			{
				t = "";
				t += phrase[i];
				sta.push(t);
				prio.push(6);
			}
		}
		outphrase = sta.top();
	}
	
}

void onp_to_inf::checkformonp()
{
	smatch ws;
	regex wrong_signs("^[a-z][-=<>\+\*\/\%\^]"); // at the beginning is letter and symbol except negation 

	if (regex_search(phrase, ws, wrong_signs)) 
	{
		outphrase = "error"; onp_correctness = 0;
	}
	else
	{
	string newphrase = "";
	smatch m;
	regex e("[-=<>\+\*\/\%\^\~]|[a-z]");

	while (regex_search(phrase, m, e))
	{
		for (unsigned i = 0; i<m.size(); ++i) {
			newphrase += phrase[m.position(i)];		//rewrite the expression except unnecessary signs
			phrase[m.position(i)] = ' ';
		}
	}
	phrase = newphrase;
	
	/*
	counting leeters and symbols
	*/
	regex _letters("[a-z]");
	auto letters_begin = sregex_iterator(phrase.begin(), phrase.end(), _letters);
	auto letters_end = sregex_iterator();

	regex _signs("[-=<>\+\*\/\%\^]");
	auto signs_begin = sregex_iterator(phrase.begin(), phrase.end(), _signs);
	auto signs_end = sregex_iterator();

	/*
	if the numbers of letters - 1 is equal numbers of symbols return 1
	*/
	if (distance(letters_begin, letters_end) - 1 != distance(signs_begin, signs_end)) 
	{
		outphrase = "error"; onp_correctness = 0;
	} 
	else onp_correctness = 1;
	}
}


