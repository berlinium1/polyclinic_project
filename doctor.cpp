#include "Header.h"

Doctor::Doctor(string name, int doctor_id, string password, string specialization) {
	this->name = name;
	this->id = doctor_id;
	this->password = password;
	this->specialization = specialization;
	personal_shedule = Timetable(doctor_id);
}
int Doctor::getDoctorId() {
	return id;
}
void Doctor::show_shedule() {
	personal_shedule.show_table();
}
string Doctor::show_password() {
	return password;
}

Timetable Doctor::getScedule() { return personal_shedule; }

string Doctor::get_name() { return name; }