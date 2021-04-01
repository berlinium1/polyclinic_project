#include "Header.h"

vector<Patient> patients;
vector<Doctor> doctors;
vector<Pharmacist> pharmacists;
vector<Therapist> therapists;
string STAFF_CODE = "Aboba1234";
int CURRENT_TIME;



void set_time() {
	int choice;
	int hour = 9;
	int min = 0;
	int counter = 1;
	cout << "-----------------------------------" << endl;
	cout << "As it is a demo program pick time:" << endl;
	for (int i = 0; i < 15; i++) {
		cout << setw(2) << setfill(' ') << counter << ") " << setw(2) << setfill(' ') << hour << ":" << setw(2) << setfill('0') << min << endl;
		counter++;
		min += 15;
		if (min > 59) {
			hour += 1;
			min = 0;
		}
	}
	cout << "Choice: " << endl;
	cin >> choice;
	CURRENT_TIME = (choice - 1) * 15;
	cout << "-----------------------------------" << endl;
}

int get_current_time() {
	return CURRENT_TIME;
}

int pick_time() {
	int choice;
	cout << "pick free time" << endl;
	cin >> choice;
	return choice - 1;
}


/*
first id number
1-Patient
2-Doctor
3-Pharmacist
4-Therapist
*/
string authorize() {
	string id, password;            
	cout << "Authorization\nid: ";
	cin >> id;
	cout << "password: ";
	cin >> password;
	if (!id.empty() && !password.empty()) {
		int role_key = id[0] - 48;
		int index = 0;

		if (role_key < 1 || role_key > 4) {
			cout << "incorrect user data!";
			return "\0";
		}

		for (size_t i = 1; i < id.length(); i++) {
			if (id[i] < 48 || id[i] > 57) {
				return "\0";
			}
			index *= 10;
			index += id[i] - 48;
		}

		if (role_key == 1) {
			if (patients.size() < index) {
				cout << "incorrect id or password was given" << endl;
				return "\0";
			}
			else {
				if (patients[index].show_password() == password) {
					return id;
				}
				return "\0";
			}
		}

		if (role_key == 2) {
			if (doctors.size() < index) {
				cout << "incorrect id or password was given" << endl;
				return "\0";
			}
			else {
				if (doctors[index].show_password() == password) {
					return id;
				}
				return "\0";
			}
		}

		if (role_key == 3) {
			if (pharmacists.size() < index) {
				cout << "incorrect id or password was given" << endl;
				return "\0";
			}
			else {
				if (pharmacists[index].password == password) {
					return id;
				}
				return "\0";
			}
		}

		if (role_key == 4) {
			if (therapists.size() < index) {
				cout << "incorrect id or password was given" << endl;
				return "\0";
			}
			else {
				if (therapists[index].show_password() == password) {
					return id;
				}
				return "\0";
			}
		}

	}
	else {
		cout << "Empty id or password was given";
		return "\0";
	}
	return "\0";
}

void register_user() {
	int choice;
	cout << "Registration\nChoose the option:\nPatient-1\nDoctor-2\nPharmacist-3\nChoice: " << endl;
	cin >> choice;
	if (choice == 1) {
		string name, password1, password2;
		int sex, age;
		cout << "Enter your name: ";
		getline(cin.ignore(), name);
		cout << "Enter your password: ";
		cin >> password1;
		cout << "Enter it again: ";
		cin >> password2;
		cout << "Choose sex:\nMan-1\nWoman-2\nYour sex: ";
		cin >> sex;
		cout << "Age: ";
		cin >> age;
		if (password1 == password2) {
			int nums = patients.size() == 0 ? 1 : int(log10(patients.size()) + 1);
			int id = pow(10, nums) + patients.size();
			patients.push_back(Patient(name, password1, id, sex, age));
			cout << "-----------------------------------" << endl;
			cout << "Done! " << name << "\nYour log in is " << id << endl;
			cout << "-----------------------------------" << endl;
		}
		else {
			cout << "passwords don't match";
		}
	}
	else {
		if (choice == 2 || choice == 3) {
			string code;
			cout << "input staff code to register as a docor or a pharmacist" << endl;
			cin >> code;
			if (code == STAFF_CODE) {
				string name, password1, password2;
				cout << "Enter your name: ";
				getline(cin.ignore(), name);
				cout << "Enter your password: ";
				cin >> password1;
				cout << "Enter it again: ";
				cin >> password2;
				if (password1 == password2) {
					if (choice == 2) {
						cout << "Choose specialization:\n";
						string spec = choose_specialization();
						if (spec == "Therapist") {
							int nums = therapists.size() == 0 ? 1 : int(log10(therapists.size()) + 1);
							int id = 4 * pow(10, nums) + therapists.size();
							therapists.push_back(Therapist(name, id, password1, spec));
							cout << "-----------------------------------" << endl;
							cout << "Done! Dr." << name << "\nYour " << spec << " log in is " << id << endl;
							cout << "-----------------------------------" << endl;
						}
						else {
							int nums = doctors.size() == 0 ? 1 : int(log10(doctors.size()) + 1);
							int id = 2 * pow(10, nums) + doctors.size();
							doctors.push_back(Doctor(name, id, password1, spec));
							cout << "-----------------------------------" << endl;
							cout << "Done! Dr." << name << "\nYour " << spec << " log in is " << id << endl;
							cout << "-----------------------------------" << endl;
						}	
					}
					else if (choice == 3) {
						int nums = pharmacists.size() == 0 ? 1 : int(log10(pharmacists.size()) + 1);
						int id = 3 * pow(10, nums) + pharmacists.size();
						pharmacists.push_back(Pharmacist(name, password1, id));
						cout << "-----------------------------------" << endl;
						cout << "Done! " << name << "\nYour pharmacist" << " log in is " << id << endl;
						cout << "-----------------------------------" << endl;
					}
					else {
						cout << "incorrect choice" << endl;
					}
				}
				else {
					cout << "passwords don't match";
				}
			}
		}
		else {
			cout << "access denied" << endl;
		}
	}
}

string choose_specialization() {
	int choice;
	cout << "-----------------------------------" << endl;
	cout << "Therapist-0\nAllergy and immunology-1\nDermatology-2\nNeurology-3\nOphthalmology-4\nOtorhinolaryngology-5\nPhysical medicine and rehabilitation-6\nPsychiatry-7\nSurgery-8\nUrology-9\nChoice: ";
	cin >> choice;
	switch(choice){
	case 0: return "Therapist";
	case 1: return "Allergy and immunology";
	case 2: return "Dermatology";
	case 3: return "Neurology";
	case 4: return "Ophthalmology";
	case 5: return "Otorhinolaryngology";
	case 6: return "Physical medicine and rehabilitation";
	case 7: return "Psychiatry";
	case 8: return "Surgery";
	case 9: return "Urology";
	default: exit(1);
	}
}

int position(int id) {
	int nums = id == 0 ? 1 : int(log10(id));
	int role = int(id / pow(10, nums));
	int i = id - role * pow(10, nums);
	return i;
}

int index(string id) {
	int res = 0;
	for (size_t i = 1; i < id.length(); i++) {
		if (id[i] < 48 || id[i] > 57) {
		}
		res *= 10;
		res += id[i] - 48;
	}
	return res;
}

void get_access(int role, int pos) {
	switch (role) {
	case 1:
		patient_work_loop(pos);
		break;
	}
}

void patient_work_loop(int pos) {
	int choice = -1;
	cout << "-----------------------------------" << endl;
	cout << "Insert 0 any time you want to leave\n";
	cout << "-----------------------------------" << endl;
	while (choice != 0) {
		cout << "-----------------------------------" << endl;
		cout << "Check info-1\nMake an appointment-2\nChoice: ";
		cin >> choice;
		cout << "-----------------------------------" << endl;
		switch (choice) {
		case 1:
			patients[pos].show_info();
			break;
		case 2:
			if (patients[pos].is_being_treated) {
				cout << "You are already being treated!" << endl;
			}
			else {
				int doc;
				cout << "Choose doctor" << endl;
				for (size_t i = 0; i < therapists.size(); i++) {
					cout << i << ") " << therapists[i].get_name() << endl;
				}
				cout << "Choice: " << endl;
				cin >> doc;
				int doc_id = therapists[doc].getDoctorId();
				Timetable table = therapists[doc].getScedule();
				table.show_table();
				int time = pick_time();
				patients[pos].make_appointment(doc, time);
			}
		}
	}
}

void appointment_name(int id) {
	int nums = id == 0 ? 1 : int(log10(id));
	int role = int(id / pow(10, nums));
	int index = id - role * pow(10, nums);
	switch (role) {
	case 2: 
		cout << "Doctor: " << doctors[index].get_name();
		break;
	case 4:
		cout << "Doctor: " << therapists[index].get_name();
	}
}

void appointment_time(int time) {
	int t = time * 15;
	int h = int(t) / 60;
	int m = t - h * 60;
	cout << " Time: " << h + 9 << ":" << m << endl;
}

void find_docs(string spec) {
	cout << "-----------------------------------" << endl;
	cout << spec << " doctors:" << endl;
	for (size_t i = 0; i < doctors.size(); i++) {
		cout << i << "--" << doctors[i].get_name() << endl;
	}
	cout << "Choice: ";
}

void doctor_working_loop(int role, int pos) {
	 if (role == 2) {
		Doctor user = doctors[pos];
		int choice = -1;
		user.getScedule().notificate(user.getDoctorId());
		cout << "-----------------------------------" << endl;
		cout << "Insert 0 any time you want to leave\n";
		cout << "-----------------------------------" << endl;
		while (choice != 0) {
			cout << "Start treatment insert-1\nCheck schedule-2" << endl;
			cin >> choice;
			switch (choice) {
			case 1:
				int pat_id;
				cout << "Insert patients id: ";
				cin >> pat_id;
				if (position(pat_id) > patients.size() || position(pat_id) < 0) {
					cout << "\nIncorrect id";
				}
				else {
					Patient patient = patients[position(pat_id)];
					patients[position(pat_id)].is_being_treated = true;
					patients[position(pat_id)].current_examination = Examination(patients[position(pat_id)].getPatientId(), user.getDoctorId(), patients[position(pat_id)].get_appointment().getTime());
					int treatment_choice = -1;
					cout << "-----------------------------------" << endl;
					cout << "Treatment menu:" << endl;
					while (treatment_choice != 0) {
						cout << "Medical card-1\nAdd recipe-2\nAdd referral-3\nAdd health problems-4\nDelete health problems-5\nChoice: ";
						cin >> treatment_choice;
						vector<string> medicines;
						string tmp = "\0";
						int doc_choice, referral_time;
						switch (treatment_choice) {
						case 1:
							patients[position(pat_id)].show_info();
							break;
						case 2:
							cout << "-----------------------------------" << endl;
							cout << "Insert the medecines and prescriptions or \"stop\" finish" << endl;
							while (true) {
								cout << "med: ";
								getline(cin, tmp);
								if (tmp == "stop") break;
								medicines.push_back(tmp);
								user.add_recipe(pat_id, medicines);
							}
							break;
						case 3:
							user.add_refferal(pat_id);
							break;
						}
					}
				}
				break;
			case 2: 
				user.getScedule().show_table();
				cout << "-----------------------------------" << endl;
				break;
			}
		}
	 }
	 if (role == 4) {
		 Therapist user = therapists[pos];
		 int choice = -1;
		 user.getScedule().notificate(user.getDoctorId());
		 cout << "-----------------------------------" << endl;
		 cout << "Insert 0 any time you want to leave\n";
		 cout << "-----------------------------------" << endl;
		 while (choice != 0) {
			 cout << "Start treatment insert-1\nCheck schedule-2" << endl;
			 cin >> choice;
			 switch (choice) {
			 case 1:
				 int pat_id;
				 cout << "Insert patients id: ";
				 cin >> pat_id;
				 if (position(pat_id) > patients.size() || position(pat_id) < 0) {
					 cout << "Incorrect id";
				 }
				 else {
					 Patient patient = patients[position(pat_id)];
					 patients[position(pat_id)].is_being_treated = true;
					 patients[position(pat_id)].current_examination = Examination(patients[position(pat_id)].getPatientId(), user.getDoctorId(), patients[position(pat_id)].get_appointment().getTime());
					 int treatment_choice = -1;
					 cout << "-----------------------------------" << endl;
					 cout << "Treatment menu:" << endl;
					 while (treatment_choice != 0) {
						 cout << "Medical card-1\nAdd recipe-2\nAdd referral-3\nAdd health problems-4\nDelete health problems-5\nFinish treatment-6\nChoice: ";
						 cin >> treatment_choice;
						 vector<string> medicines;
						 string tmp = "\0";
						 int doc_choice, referral_time;
						 switch (treatment_choice) {
						 case 1:
							 patients[position(pat_id)].show_info();
							 break;
						 case 2:
							 cout << "-----------------------------------" << endl;
							 cout << "Insert the medecines and prescriptions or \"stop\" finish" << endl;
							 while (true) {
								 cout << "med: ";
								 getline(cin, tmp);
								 if (tmp == "stop") break;
								 medicines.push_back(tmp);
								 user.add_recipe(pat_id, medicines);
							 }
							 break;
						 case 3:
							 user.add_refferal(pat_id);
							 break;
						 case 6:
							 user.finish_treatment(pat_id);
							 break;
						 }
					 }
				 }
				 break;
			 case 2:
				 user.getScedule().show_table();
				 cout << "-----------------------------------" << endl;
				 break;
			 }
		 }
	 }
}

void pharmacist_working_loop(int pos) {
	Pharmacist user = pharmacists[pos];
	int choice = -1;
	while (choice != 0) {
		cout << "-----------------------------------" << endl;
		cout << "Exit-0\nCheck recipe-1\nChoice: ";
		cin >> choice;
		if (choice == 1) {
			int pat_id;
			cout << "Insert the patient id: ";
			cin >> pat_id;
			user.show_recipe(pat_id);
		}
	}
}

void main_loop() {
	int c = -1;
	while (c != 0) {
		cout << "exit-0\nregister-1\nlog in-2\nset time-3\n";
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
		if (c == 3) {
			set_time();
		}
	}
}