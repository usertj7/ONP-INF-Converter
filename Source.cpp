#include<iostream>
#include<string>
#include "functions_and_checkers.h"
#include "onp_to_inf.h"
#include "inf_to_onp.h"

using namespace std;


int main() {

	int x_coord[] = { 1,0,0 };
	int y_coord[] = { 1,2,2 };
	string menu_options[] = { "INF -> ONP", "ONP -> INF", "ESC TO EXIT" };
	void(inf_to_onp::*inf_to_onp_func[6])();
	inf_to_onp_func[0] = &inf_to_onp::call_inf_to_onp_from_file;
	inf_to_onp_func[1] = &inf_to_onp::input_phrase1;
	inf_to_onp_func[2] = &inf_to_onp::deleteothersymbols;
	inf_to_onp_func[3] = &inf_to_onp::check_form_inf;
	inf_to_onp_func[4] = &inf_to_onp::inftoonp;
	inf_to_onp_func[5] = &inf_to_onp::inputtofile;

	void(onp_to_inf::*onp_to_inf_func[5])();
	onp_to_inf_func[0] = &onp_to_inf::call_onp_to_inf_from_file;
	onp_to_inf_func[1] = &onp_to_inf::input_phrase;
	onp_to_inf_func[2] = &onp_to_inf::checkformonp;
	onp_to_inf_func[3] = &onp_to_inf::onptoinf;
	onp_to_inf_func[4] = &onp_to_inf::inputtofile;
	
	menu(x_coord, y_coord, menu_options, 3, inf_to_onp_func, onp_to_inf_func);
	
	return 0;
}