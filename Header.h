#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <cmath>
using namespace std;

class Patient {
public:
	string password, name;
	int id;
	Patient(string name, string password, int id) {
		this->name = name;
		this->password = password;
		this->id = id;
	}
};

class Doctor {
public:
	string password, name, specialization;
	int id;
	Doctor(string name, string password, int id, string specialization) {
		this->name = name;
		this->password = password;
		this->id = id;
		this->specialization = specialization;
	}
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

class Therapist {
public:
	string password, name, specialization;
	int id;
	Therapist(string name, string password, int id, string specialization) {
		this->name = name;
		this->password = password;
		this->id = id;
		this->specialization = specialization;
	}
};

class Appointment {
private:
	int time;
	int patient_id;
public:
	Appointment();
	Appointment(int patient, int time);
	int getTime();
	int getPatientId();
};

class Timetable {
private:
	int doctor_id;
	string doctor_name;
	Appointment* appointments;
public:
	Timetable(int doctor_id);
	~Timetable();
	void add_appointment(int time, int patient_id);
	void notificate(int doctor_id);
	void show_table();
};

int pick_time();
string authorize();
void register_user();
string choose_specialization();

extern vector<Patient> patients;
extern vector<Doctor> doctors;
extern vector<Pharmacist> pharmacists;
extern string STAFF_CODE;