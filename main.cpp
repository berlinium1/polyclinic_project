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
	CURRENT_TIME = 45;
	register_user();
	register_user();
	string res = authorize();
	if (res != "\0") {
		int role_key = res[0];
		int pos = index(res);
		patient_work_loop(pos);
	}
	return 0;
}