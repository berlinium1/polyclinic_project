#include "Header.h"

Patient::Patient(string name, string password, int id, int sex, int age) {
	this->name = name;
	this->password = password;
	this->id = id;
	this->age = age;
	this->sex = sex;
}

void Patient::make_appointment(int doctor_index, int time) {
	if (current_appointment.getDoctor() == NULL) {
		Timetable table = therapists[doctor_index].getScedule();
		int doc_id = therapists[doctor_index].getDoctorId();
		table.add_appointment(time * 15, id, doc_id);
		current_appointment = Appointment(id, doc_id, time);
		table.show_table();
	}
	else {
		cout << "You already have an appointment!" << endl;
	}
}

void Patient::show_info() {
	cout << "-----------------------------------" << endl;
	string s = sex == 1 ? "man" : "woman";
	cout << name << endl << "sex: " << s << "|" << " age: " << age << endl;
	if (health_problems.size() > 0) {
		cout << "health problems: " << endl;
		for (size_t i = 0; i < health_problems.size(); i++) {
			cout << i << ") " << health_problems[i] << endl;
		}
	}
	if (current_appointment.getDoctor() != NULL) {
		cout << "-----------------------------------" << endl;
		cout << "Current appointment: " << endl;
		appointment_name(current_appointment.getDoctor());
		appointment_time(current_appointment.getTime());
		cout << "-----------------------------------" << endl;
	}
}

int Patient::getPatientId() {
	return id;
}

string Patient::show_password() {
	return password;
}