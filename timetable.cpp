#include "Header.h"

Appointment::Appointment() {
	this->time = NULL;
	this->patient_id = NULL;
}

Appointment::Appointment(int patient, int doctor_id, int time) {
	this->patient_id = patient;
	this->doctor_id = doctor_id;
	this->time = time;
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
			cout << setw(2) << setfill(' ') << counter << ") " << setw(2) << setfill(' ') << hour << ":" << setw(2) << setfill('0') << min << " Taken by " << appointments[i].getPatientId() << endl;
			counter++;
			min += 15;
			if (min > 59) {
				hour += 1;
				min = 0;
			}
		}
	}
}

void Timetable::add_appointment(int time, int patient_id, int doctor_id) {
	if (appointments[time/15].getTime() == NULL) {
		appointments[time/15] = Appointment(patient_id, doctor_id, time);
	}
}

void Timetable::notificate(int doctor_id) {
	for (int i = 0; i < 15; i++) {
		if (get_current_time() == i * 15) {
			if (appointments[i].getTime() != NULL) {
				int patient = appointments[i].getPatientId();
				int nums = patient == 0 ? 1 : int(log10(patient));
				int role = int(patient / pow(10, nums));
				int index = patient - role * pow(10, nums);
				cout << "A patient is about to come. Be ready. " << endl;
				int t = i * 15;
				int h = int(t) / 60;
				int m = t - h * 60;
				cout << " Time: " << h + 9 << ":" << m << endl;
				patients[index].show_info();
			}
		}
	}
}