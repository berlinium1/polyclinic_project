#include <iostream>
#include <string>
#include <iomanip> 
using namespace std;

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