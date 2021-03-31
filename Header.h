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
	bool mark_as_held() {
		was_held = true;
	};
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

class Recipe {
	int patient_id;
	bool is_given = false;
public:
	vector<string> medicines;
	Recipe() {}
	Recipe(int patient_id, vector<string> meds) {
		this->patient_id = patient_id;
		this->medicines = meds;
	}
	void set_as_given() { is_given = true; }
};

class Patient {
	int id;
	string password;
	string name;
	int sex;
	int age;
	vector<string> health_problems;
	vector<Examination> previous_examintions;
	Appointment current_appointment = Appointment(id, NULL, NULL);

public:
	Examination current_examination = Examination(id, NULL, NULL);
	Recipe current_recipe = Recipe();
	bool is_being_treated = false;
	int getPatientId();
	Patient(string name, string password, int id, int sex, int age);
	string show_password();
	void make_appointment(int doctor_id, int time);
	Appointment get_appointment() { return current_appointment; }
	void show_info();
};

class Doctor {
	int id;
	string password;
	string name;
	string specialization;
	friend class Timetable;
	Timetable personal_shedule;


public:

	Doctor(string name, int doctor_id, string password, string specialization);
	int getDoctorId();
	void show_shedule();
	string show_password();
	Timetable getScedule();
	string get_name();

	void check_medical();
	void finish_treatment(int patient_id);
	void add_recipe(int patient_id, vector<string> medicines);
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
void set_time();
int get_current_time();
string authorize();
void register_user();
string choose_specialization();
int index(string);
void appointment_name(int);
void appointment_time(int);
void patient_work_loop(int);
void doctor_working_loop(int, int);
void pharmacist_working_loop(int);
int position(int);

extern vector<Patient> patients;
extern vector<Doctor> doctors;
extern vector<Pharmacist> pharmacists;
extern vector<Therapist> therapists;