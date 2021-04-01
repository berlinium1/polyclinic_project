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

void Doctor::add_refferal(int pat_id) {
	cout << "-----------------------------------" << endl;
	cout << "Referral menu:\n";
	int doc_choice, referral_time;
	string tmp = choose_specialization();
	find_docs(tmp);
	cin >> doc_choice;
	doctors[doc_choice].getScedule().show_table();
	referral_time = pick_time();
	doctors[doc_choice].getScedule().add_appointment(referral_time * 15, pat_id, doctors[doc_choice].getDoctorId());
	patients[position(pat_id)].set_appointment(Appointment(patients[position(pat_id)].getPatientId(), doctors[doc_choice].getDoctorId(), referral_time));
}

void Therapist::finish_treatment(int patient_id) {
	int pos = position(patient_id);
	Patient patient = patients[pos];
	patient.previous_examintions.push_back(patient.current_examination);
	patient.current_examination = Examination(patient.getPatientId(), NULL, NULL);
	patient.is_being_treated = false;
}

void Pharmacist::mark_as_given(int pat_id) {
	int pat_pos = position(pat_id);
	patients[pat_pos].current_recipe.set_as_given();
}

void Pharmacist::show_recipe(int pat_id) {
	int pat_pos = position(pat_id);
	Recipe rec = patients[pat_pos].current_recipe;
	vector<string> meds = rec.medicines;
	cout << "-----------------------------------" << endl;
	cout << "Recipe";
	for (size_t i = 0; i < meds.size(); i++) {
		cout << meds[i] << endl;
	}
	if (meds.empty()) {
		cout << "Empty recipe!" << endl;
	}
	else {
		int choice;
		cout << "Mark as given?\nNo-0\nYes-1\nChoice: ";
		cin >> choice;
		if (choice == 1) mark_as_given(pat_id);
	}
}