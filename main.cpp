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
	set_time();
	int c = -1;
	while (c != 0) {
		cout << "exit-0\nregister-1\nlog in-2\n";
		cout << "-----------------------------------" << endl;
		cin >> c;
		if (c == 1) {
			register_user();
			cout << "-----------------------------------" << endl;
		}
		if (c == 2) {
			string res = authorize();
			int role_key = res[0] - 48;
			int pos = index(res);
			cout << "parsed: " << role_key << " " << pos << endl;
			switch (role_key) {
			case 1:
				patient_work_loop(pos);
				break;
			case 2:
				doctor_working_loop(role_key, pos);
				break;
			case 3:
				pharmacist_working_loop(pos);
				break;
			case 4:
				doctor_working_loop(role_key, pos);
				break;
			}
		}
	}
	return 0;
}