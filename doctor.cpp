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

void Doctor::add_recipe(int id, vector<string> meds) {
	int nums = id == 0 ? 1 : int(log10(id));
	int role = int(id / pow(10, nums));
	int index = id - role * pow(10, nums);
	patients[index].current_recipe = Recipe(index, meds);
}

void Therapist::finish_treatment(int patient_id) {
	int pos = position(patient_id);
	Patient patient = patients[pos];
	patient.previous_examintions.push_back(patient.current_examination);
	patient.current_examination = Examination(patient.getPatientId(), NULL, NULL);
	patient.is_being_treated = false;
}