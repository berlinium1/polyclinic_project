#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <cmath>
using namespace std;

void appointment_name(int);
void appointment_time(int);

class Examination {
	int patient_id;
	int time;
	int doctor_id;
	bool was_held = false;
public:
	Examination(int patient_id, int doctor_id, int time) {
		this->patient_id = patient_id;
		this->doctor_id = doctor_id;
		this->time = time;
	}

	void create_recipe(string* medicines);
	void make_referral(int patient_id, int doctor_id);
	bool mark_as_held();
};

class Appointment {
private:
	int time;
	int patient_id;
	int doctor_id;
public:
	Appointment();
	Appointment(int patient, int doctor_id, int time) {
		this->patient_id = patient;
		this->doctor_id = doctor_id;
		this->time = time;
	}
	int getTime();
	int getPatientId() { return patient_id; }
	int getDoctor() { return doctor_id; }
};

class Timetable {
private:
	int doctor_id = NULL;
	string doctor_name;
	Appointment* appointments;
public:
	Timetable() {};
	Timetable(int doctor_id);
	~Timetable();
	void add_appointment(int, int, int);
	void notificate(int doctor_id);
	void show_table();
};

class Patient {
	int id;
	string password;
	string name;
	int sex;
	int age;
	vector<string> health_problems;
	vector<Examination> previous_examintions;
	Examination current_examination = Examination(id, NULL, NULL);
	Appointment current_appointment = Appointment(id, NULL, NULL);
	//Recipe current_recipe = NULL

public:
	int getPatientId() {
		return id;
	}

	Patient(string name, string password, int id, int sex, int age) {
		this->name = name;
		this->password = password;
		this->id = id;
		this->age = age;
		this->sex = sex;
	}

	string show_password() {
		return password;
	}

	void make_appointment(int doctor_id, int time) {
		
	}

	void show_info() {
		cout << "-----------------------------------" << endl;
		string s = sex == 1 ? "man" : "woman";
		cout << name << endl << "sex: " << s << "|" << " age: " << age << endl;
		if (health_problems.size() > 0) {
			cout << "health problems: " << endl;
			for (size_t i = 0; i < health_problems.size(); i++) {
				cout << i << ") " << health_problems[i] << endl;
			}
			if (current_appointment.getTime() != NULL) {
				cout << "-----------------------------------" << endl;
				cout << "Current appointment: " << endl;
				appointment_name(current_appointment.getDoctor());
				appointment_time(current_appointment.getTime());
				cout << "-----------------------------------" << endl;
			}
		}
	}
};

class Doctor {
	int id;
	string password;
	string name;
	string specialization;
	friend class Timetable;
	Timetable personal_shedule;


public:

	Doctor(string name, int doctor_id, string password, string specialization) {
		this->name = name;
		this->id = doctor_id;
		this->password = password;
		this->specialization = specialization;
		personal_shedule = Timetable(doctor_id);
	}
	int getDoctorId() {
		return id;
	}
	void show_shedule() {
		personal_shedule.show_table();
	}
	string show_password() {
		return password;
	}

	Timetable getScedule() { return personal_shedule; }

	string get_name() { return name; }
	void check_medical();
	void finish_treatment(int patient_id);
	void add_recipe(int patient_id, string* medicines);
	void add_refferal(int patient_id, int doctor_id, string purpose);
	void new_examination(int doctor_id);
	void add_health_problems(vector<string> problems);
	void remove_health_problems(vector<string> problems);
};

class Pharmacist {
public:
	string password, name;
	int id;
	Pharmacist(string name, string password, int id) {
		this->name = name;
		this->password = password;
		this->id = id;
	}
};

class Therapist : public Doctor {
public:
	Therapist(string name, int doctor_id, string password, string specialization) :Doctor(name, doctor_id, password, specialization) {}
	void finish_treatment(int patient_id);
};

int pick_time();
string authorize();
void register_user();
string choose_specialization();
int index(string);
void appointment_name(int);
void appointment_time(int);
void patient_work_loop(int pos);

extern vector<Patient> patients;
extern vector<Doctor> doctors;
extern vector<Pharmacist> pharmacists;
extern string STAFF_CODE;