
#include "functions_and_checkers.h"
#include "onp_to_inf.h"
#include "inf_to_onp.h"
using namespace std;



void position(const int x, const int y)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void menu(int *x_parameters, int *y_parameters, string *tab, int size, void(inf_to_onp::*inf_to_onp_tab_func[])(), void(onp_to_inf::*onp_to_inf_tab_func[])())
{
	

	string previous_menu_options_tab[] = { "INF -> ONP", "ONP -> INF", "ESC TO EXIT" };

	string menu_options_tab[] = { "LOAD DATA FROM THE FILE", "ENTER DATA IN THE CONSOLE", "ESC TO EXIT" };
	int x_as[3] = { 1,0,0 };
	int y_as[3] = { 1,2,2 };
	inf_to_onp ito;
	onp_to_inf oti;
	
	system("cls");
	int x_1 = x_parameters[0] + 2, y_1 = y_parameters[0];
	for (int i = 0; i < size; i++)
	{
		position(x_1, y_1);
		cout << tab[i];
		x_1 += x_parameters[1];
		y_1 += y_parameters[1];
	}


	int x = 0;
	int x_b;
	int y = 0;
	int y_b;
	char c;

	do
	{	//set menu pointer on position 
		position(x_parameters[0] + x * x_parameters[1], y_parameters[0] + y * y_parameters[1]);
		cout << static_cast<char>(62);//menu pointer
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
		case 13:	//press enter == call function
			switch (y)
			{
			case 0:
				Menu<inf_to_onp, void>m;

				m._menu(x_as, y_as, menu_options_tab, 3, previous_menu_options_tab, 3, ito, inf_to_onp_tab_func, 6);
				break;
			case 1:
				Menu<onp_to_inf, void>m_1;

				m_1._menu(x_as, y_as, menu_options_tab, 3, previous_menu_options_tab, 3, oti, onp_to_inf_tab_func, 5);
				break;
			}

		}//delete last indicator of menu pointer
		position(x_parameters[0] + x_b * x_parameters[1], y_parameters[0] + y_b * y_parameters[1]);
		cout << " ";
	} while (c != 27);

}