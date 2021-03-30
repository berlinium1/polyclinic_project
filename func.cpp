#include "Header.h"

vector<Patient> patients;
vector<Doctor> doctors;
vector<Pharmacist> pharmacists;
vector<Therapist> therapists;
string STAFF_CODE = "Aboba1234";

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
				if (patients[index].password == password) {
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
				if (doctors[index].password == password) {
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
				if (therapists[index].password == password) {
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
		cout << "Enter your name: ";
		getline(cin.ignore(), name);
		cout << "Enter your password: ";
		cin >> password1;
		cout << "Enter it again: ";
		cin >> password2;
		if (password1 == password2) {
			int nums = patients.size() == 0 ? 1 : int(log10(patients.size()) + 1);
			int id = pow(10, nums) + patients.size();
			patients.push_back(Patient(name, password1, id));
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
							therapists.push_back(Therapist(name, password1, id, spec));
							cout << "-----------------------------------" << endl;
							cout << "Done! Dr." << name << "\nYour " << spec << " log in is " << id << endl;
							cout << "-----------------------------------" << endl;
						}
						else {
							int nums = doctors.size() == 0 ? 1 : int(log10(doctors.size()) + 1);
							int id = 2 * pow(10, nums) + doctors.size();
							doctors.push_back(Doctor(name, password1, id, spec));
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