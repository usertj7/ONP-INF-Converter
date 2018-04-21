#ifndef MENU_H
#define MENU_H
#include<iostream>
#include <stack>
#include <windows.h>
#include <cstdio>
#include <conio.h>
using namespace std;

template<typename type1, typename type2>class Menu
{
public:
	/*
	function that sets cursor on x, y position
	*/
	void position(const int x, const int y)
	{
		COORD coord = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}

	/*
	template of menu function
	x_parameters: x[0] - x coordinate, x[1]- space between two x positions, x[2] -number of x's menu positions
	y_parameters: same as x's
	tab- names of menu options
	size - tab size
	tab_m - names of previous menu options
	size_m - tab_m size
	object - object type1 type
	func_tab - array of pointers to the functions
	func_tab_size - func_tab_size 
	*/
	void _menu(int *x_parameters, int *y_parameters, string *tab, int size, string *tab_m, int size_m, type1 object, type2(type1::*func_tab[])(), int func_tab_size)
	{
		system("cls");
		//show menu options
		int x_1 = x_parameters[0] + 2, y_1 = y_parameters[0];
		for (int i = 0; i < size; i++)
		{
			position(x_1, y_1);
			cout << tab[i];
			x_1 += x_parameters[1];
			y_1 += y_parameters[1];
		}

		//set initial values
		int x = 0;
		int x_b;
		int y = 0;
		int y_b;

		char c;


		do
		{	//set menu pointer on position 
			position(x_parameters[0] + x * x_parameters[1], y_parameters[0] + y * y_parameters[1]);
			cout << static_cast<char>(62); //menu pointer
										   //x_b, y_b variables used to delete last indicator of pointer
			y_b = y;
			x_b = x;
			c = _getch();
			switch (c)
			{
			case 224:
			{

			case 72:  //up
			{
				if (y > 0) y--;
				else y = y_parameters[2] - 1;

				break;
			}
			case 77: //right
			{
				if (x < x_parameters[2] - 1) x++;
				else x = 0;

				break;
			}
			case 75:  //left
			{
				if (x>0) x--;
				else x = x_parameters[2] - 1;
				break;
			}
			case 80:  //down
			{
				if (y<y_parameters[2] - 1) y++;
				else y = 0;
				break;
			}



			break;
			}
			case 13: //press enter == call function
				switch (y)
				{
				case 0:
					(object.*(func_tab[y]))();
					break;
				case 1:
					for (int i = 1; i < func_tab_size; i++)
					{
						(object.*(func_tab[i]))();
					}

				}
				system("cls");
				//show menu options
				x_1 = x_parameters[0] + 2; y_1 = y_parameters[0];
				for (int i = 0; i < size; i++)
				{
					position(x_1, y_1);
					cout << tab[i];
					x_1 += x_parameters[1];
					y_1 += y_parameters[1];
				}
			}
			//delete last indicator of menu pointer
			position(x_parameters[0] + x_b * x_parameters[1], y_parameters[0] + y_b * y_parameters[1]);
			cout << " ";
		} while (c != 27);

		//show previous menu
		system("cls");
		x_1 = x_parameters[0] + 2; y_1 = y_parameters[0];
		for (int i = 0; i < size_m; i++)
		{
			position(x_1, y_1);
			cout << tab_m[i];
			x_1 += x_parameters[1];
			y_1 += y_parameters[1];
		}


	}
};


#endif
