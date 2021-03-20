#include "Header.h"

Appointment::Appointment() {
	this->time = NULL;
	this->patient_id = NULL;
}

Appointment::Appointment(int patient_id, int time) {
	this->time = time;
	this->patient_id = patient_id;
}

int Appointment::getTime() {
	return time;
}

Timetable::Timetable(int doctor_id) {
	this->doctor_id = doctor_id;
	this->doctor_name = "Test doctor";
	this->appointments = new Appointment[15];
}

Timetable::~Timetable() {
	

}

void Timetable::show_table() {
	int hour = 9;
	int min = 0;
	int counter = 1;
	for (int i = 0; i < 15; i++) {
		if (appointments[i].getTime() == NULL) {
			cout << setw(2) << setfill(' ') << counter << ") " << setw(2) << setfill(' ') << hour << ":" << setw(2) << setfill('0') << min << " FREE" << endl;
			counter++;
			min += 15;
			if (min > 59) {
				hour += 1;
				min = 0;
			}
		}
		else {
			cout << setw(2) << setfill(' ') << counter << ") " << setw(2) << setfill(' ') << hour << ":" << setw(2) << setfill('0') << min << " Taken" << endl;
			counter++;
			min += 15;
			if (min > 59) {
				hour += 1;
				min = 0;
			}
		}
	}
}

void Timetable::add_appointment(int time, int patient_id) {
	if (appointments[time/15].getTime() == NULL) {
		appointments[time/15] = Appointment(patient_id, time);
	}
}