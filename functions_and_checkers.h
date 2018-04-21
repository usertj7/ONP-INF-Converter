#ifndef FUNCTIONS_AND_CHECKERS_H
#define FUNCTIONS_AND_CHECKERS_H
#include<iostream>
#include<string>
#include <windows.h>
#include "onp_to_inf.h"
#include "inf_to_onp.h"
#include "menu.h"

void position(const int x, const int y);
/*
menu function
x_parameters: x[0] - x coordinate, x[1]- space between two x positions, x[2] -number of x's menu positions
y_parameters: same as x's
tab- names of menu options
inf_to_onp_tab_func - array of pointers to the functions
onp_to_inf_tab_func - array of pointers to the functions
*/
void menu(int *x_parameters, int *y_parameters, string *tab, int size, void(inf_to_onp::*inf_to_onp_tab_func[])(), void(onp_to_inf::*onp_to_inf_tab_func[])());

#endif
