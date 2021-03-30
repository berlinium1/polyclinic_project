#include "Header.h"

int main() {
	/*
	Timetable table(10);
	table.show_table();
	int time = pick_time();
	table.add_appointment(time * 15, 12);
	table.show_table();
	*/
	//users

	register_user();
	string res = authorize();
	if (res != "\0") cout << res << "FOUND";
	return 0;
}