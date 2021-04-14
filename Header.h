
#ifndef Header_h
#define Header_h

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <cmath>
#include <limits>
using namespace std;

class Examination {
public:
    int patient_id;
    int time;
    int doctor_id;
    bool was_held = false;
    Examination(int patient_id, int doctor_id, int time) {
        this->patient_id = patient_id;
        this->doctor_id = doctor_id;
        this->time = time;
    }
};

class Appointment {
private:
    int time;
    int patient_id;
    int doctor_id;
public:
    Appointment();
    Appointment(int patient, int doctor_id, int time);
    int getTime();
    int getPatientId() { return patient_id; }
    int getDoctor() { return doctor_id; }
};

class Timetable {
private:
    int doctor_id = NULL;
    string doctor_name;
public:
    Appointment* appointments;
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
    Appointment current_appointment;

public:
    vector<string> health_problems;
    vector<Examination> previous_examintions;
    Examination current_examination = Examination(id, NULL, NULL);
    Recipe current_recipe = Recipe();
    bool is_being_treated = false;
    int getPatientId();
    Patient(string name, string password, int id, int sex, int age);
    string show_password();
    void make_appointment(int doctor_id, int time);
    Appointment get_appointment();
    void set_appointment(Appointment);
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
    Timetable getShedule();
    string get_name();
    void add_recipe(int patient_id, vector<string> medicines);
    void add_refferal(int patient_id);
    void add_health_problems(int patient_id, vector<string> problems);
    void remove_health_problems(int patient_id, vector<string> problems);
    string get_spec();
};

class Pharmacist {
public:
    string password, name;
    int id;
    Pharmacist(string name, string password, int id);
    void show_recipe(int id);
    void mark_as_given(int id);
};

class Therapist : public Doctor {
public:
    Therapist(string name, int doctor_id, string password, string specialization) :Doctor(name, doctor_id, password, specialization) {}
    void finish_treatment(int patient_id);
};

int correct_input(int, int);
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
void main_loop();
void find_docs(string);

extern vector<Patient> patients;
extern vector<Doctor> doctors;
extern vector<Pharmacist> pharmacists;
extern vector<Therapist> therapists;
#endif /* Header_h */
