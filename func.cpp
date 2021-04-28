#include "Header.h"

vector<Patient> patients;
vector<Doctor> doctors;
vector<Pharmacist> pharmacists;
vector<Therapist> therapists;
string STAFF_CODE = "code1234";
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
    choice = correct_input(1, 15);
    CURRENT_TIME = (choice - 1) * 15;

    cout << "-----------------------------------" << endl;
}

int get_current_time() {
    return CURRENT_TIME;
}

int correct_input(int first, int last) // для выбора цифры
{
    int choice;
    bool input;

    do
    {
        cout << "Choice: ";

        input = true;
        cin >> choice;
        if (cin.fail() || choice < first || choice > last)
        {
            input = false;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please, try again.\n";
        }
    } while (!input);

    return choice;
}

int correct_id(int prompt_role, string error_report) // для ввода айди с приявязкой к роли 
{                                                    // если хотим получить айди пациента, вводим 1, если врача 2 и тд
    int id, nums, role, pos;                         // иначе мы можем ввести айди терапевта/врача/фармацевта вместо айди пациента, 
    bool input;                                      // когда врач вводит айди чтобы лечить (doctor_working_loop -> 391)

    do
    {
        cout << "Choice: ";
        input = true;
        cin >> id;

        nums = id == 0 ? 1 : int(log10(id));
        role = int(id / pow(10, nums));
        pos = id - role * pow(10, nums);

        if (cin.fail() || role != prompt_role || id < 10)   // отличается от следующей ф-ии только этой строкой 
        {
            input = false;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            switch (prompt_role)
            {
            case 1: if (pos >= patients.size()) input = false; break;
            case 2: if (pos >= doctors.size()) input = false; break;
            case 3: if (pos >= pharmacists.size()) input = false; break;
            case 4: if (pos >= therapists.size()) input = false; break;
            }
        }
        if (!input) cout << error_report + "\n";
    } while (!input);

    return id;
}

int correct_id(string error_report)     // для ввода айди без привязки к роли
{
    int id, nums, role, pos;
    bool input;

    do
    {
        cout << "Choice: ";
        input = true;
        cin >> id;

        nums = id == 0 ? 1 : int(log10(id));
        role = int(id / pow(10, nums));
        pos = id - role * pow(10, nums);

        if (cin.fail() || id < 10)
        {
            input = false;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            switch (role)
            {
            case 1: if (pos >= patients.size()) input = false; break;
            case 2: if (pos >= doctors.size()) input = false; break;
            case 3: if (pos >= pharmacists.size()) input = false; break;
            case 4: if (pos >= therapists.size()) input = false; break;
            }
        }    
        if (!input) cout << error_report + "\n";
    } while (!input);
    return id;
}



/*
first id number
1-Patient
2-Doctor
3-Pharmacist
4-Therapist
*/
string authorize() {
    int id;
    string password;
    cout << "Authorization\n Enter ID.\n";
    id = correct_id("You entered invalid ID. Please, try again.");
    cout << "password: ";
    cin >> password;
    cout << "-----------------------------------" << endl;
    
    if (!password.empty())
    {
        int nums = id == 0 ? 1 : int(log10(id));
        int role = int(id / pow(10, nums));
        int pos = id - role * pow(10, nums);
        
        switch (role)
        {
        case 1: if (password == patients[pos].show_password()) return to_string(id); else return "\n"; break;
        case 2: if (password == doctors[pos].show_password()) return to_string(id); else return "\n"; break;
        case 3: if (password == pharmacists[pos].password) return to_string(id); else return "\n"; break;
        case 4: if (password == therapists[pos].show_password()) return to_string(id); else return "\n"; break;
        }
    }
    else return "\n";
}

void register_user() {
    int choice;
    cout << "Registration\nChoose the option:\nPatient-1\nDoctor-2\nPharmacist-3" << endl;
    choice = correct_input(1, 3);
    if (choice == 1) {
        string name, password1, password2;
        int sex, age;
        cout << "Enter your name: ";
        getline(cin.ignore(), name);
        cout << "Enter your password: ";
        cin >> password1;
        cout << "Enter it again: ";
        cin >> password2;
        cout << "Choose sex:\nMan-1\nWoman-2\n";
        sex = correct_input(1, 2);
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
            cout << "passwords don't match\n";
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
    cout << "Therapist-0\nAllergy and immunology-1\nDermatology-2\nNeurology-3\nOphthalmology-4\nOtorhinolaryngology-5\nPhysical medicine and rehabilitation-6\nPsychiatry-7\nSurgery-8\nUrology-9\n";
    choice = correct_input(0, 9);
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
        cout << "Check info-1\nMake an appointment-2\n";
        choice = correct_input(0,2);
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
                if (therapists.size() == 0) {
                    cout<<"There's no doctor available to choose.\n";
                    break;
                }
                for (size_t i = 0; i < therapists.size(); i++) {
                    cout << i << ") " << therapists[i].get_name() << endl;
                }
                //cout << "Choice: " << endl;
                doc = correct_input(0, therapists.size());
                Timetable table = therapists[doc].getShedule();
                table.show_table();
                while (true) {
                    int time = correct_input(1, 15) - 1;
                    if (time == -1) break;
                    if (therapists[doc].getShedule().appointments[time].getTime() != NULL) {
                        cout<<"Pay attention: this time's already occupied. Choose another variant.\n";
                    }
                    else{
                    patients[pos].make_appointment(doc, time);
                        break;
                    }
                }
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
        cout << "Doctor: " << doctors[index].get_name() << " " << doctors[index].get_spec();
        break;
    case 4:
        cout << "Doctor: " << therapists[index].get_name() << " Therapist";
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
        if (spec == doctors[i].get_spec())
        {
            cout << doctors[i].getDoctorId() << "--" << doctors[i].get_name() << endl;
        }
    }
}

void doctor_working_loop(int role, int pos) {
     if (role == 2) {
        Doctor user = doctors[pos];
        int choice = 1;
        user.getShedule().notificate(user.getDoctorId());
        cout << "-----------------------------------" << endl;
        cout << "Insert 0 any time you want to leave\n";
        cout << "-----------------------------------" << endl;
        while (choice != 0) {
            cout << "Start treatment insert-1\nCheck schedule-2" << endl;
            choice = correct_input(0, 2);
            switch (choice) {
            case 1:
                int pat_id;
                cout << "Insert patients id.\n";
                pat_id = correct_id(1, "No patients with such ID.");
                if (position(pat_id) > patients.size() || position(pat_id) < 0) {
                    cout << "\nIncorrect id";
                }
                else {
                    Patient patient = patients[position(pat_id)];
                    patients[position(pat_id)].is_being_treated = true;
                    patients[position(pat_id)].current_examination = Examination(patients[position(pat_id)].getPatientId(), user.getDoctorId(), patients[position(pat_id)].get_appointment().getTime());
                    int treatment_choice = 1;
                    cout << "-----------------------------------" << endl;
                    cout << "Treatment menu:" << endl;
                    while (treatment_choice != 0) {
                        cout << "Medical card-1\nAdd recipe-2\nAdd referral-3\nAdd health problems-4\nDelete health problems-5\n";
                        treatment_choice = correct_input(0, 5);
                        switch (treatment_choice) {
                        case 1:
                            patients[position(pat_id)].show_info();
                            break;
                            case 2:{
                            vector<string> medicines;
                            string tmp = "\0";
                            cout << "-----------------------------------" << endl;
                            cout << "Insert the medicines and prescriptions or \"stop\" finish" << endl;
                            cin.ignore();
                            while (true) {
                                cout << "med: " ;
                                getline(cin, tmp);
                                if (tmp == "stop") break;
                                medicines.push_back(tmp);
                                user.add_recipe(pat_id, medicines);
                            }
                            }
                            break;
                            case 3:
                               user.add_refferal(pat_id);
                               break;
                            case 4:{
                                    vector<string> healthProblems;
                                    string temp = "\0";
                                    cout << "-----------------------------------" << endl;
                                    cout << "Insert patient's health problems which you've detected or \"stop\" finish" << endl;
                                    cin.ignore();
                                    while (true) {
                                        cout << "Problem: " ;
                                        getline(cin, temp);
                                        if (temp == "stop") break;
                                        healthProblems.push_back(temp);
                                        user.add_health_problems(pat_id, healthProblems);
                                    }
                                    break;
                                }
                             case 5:{
                                    vector<string> curedHealthProblems;
                                    string temp = "\0";
                                    cout << "-----------------------------------" << endl;
                                    cout << "Erase patient's problems whish were cured or \"stop\" finish" << endl;
                                    cin.ignore();
                                    while (true) {
                                        cout << "Problem: " ;
                                        getline(cin, temp);
                                        if (temp == "stop") break;
                                        curedHealthProblems.push_back(temp);
                                        user.remove_health_problems(pat_id, curedHealthProblems);
                                    }
                                    break;
                                }
                            default:
                                cout<<"Try again\n";
                        }
                    }
                }
                break;
            case 2:
                user.getShedule().show_table();
                cout << "-----------------------------------" << endl;
                break;
            default:
                    cout<<"Try again\n";
            }
        }
     }
     if (role == 4) {
         Therapist user = therapists[pos];
         int choice = 1;
         user.getShedule().notificate(user.getDoctorId());
         cout << "-----------------------------------" << endl;
         cout << "Insert 0 any time you want to leave\n";
         cout << "-----------------------------------" << endl;
         while (choice != 0) {
             cout << "Start treatment insert-1\nCheck schedule-2" << endl;
             choice = correct_input(0, 2);
             switch (choice) {
             case 1:
                 int pat_id;
                 cout << "Insert patients id. \n ";
                 pat_id = correct_id(1, "No patients with such ID.");

                 if (position(pat_id) > patients.size() || position(pat_id) < 0) {
                     cout << "Incorrect id";
                 }
                 else {
                     Patient patient = patients[position(pat_id)];
                     patients[position(pat_id)].is_being_treated = true;
                     patients[position(pat_id)].current_examination = Examination(patients[position(pat_id)].getPatientId(), user.getDoctorId(), patients[position(pat_id)].get_appointment().getTime());
                     int treatment_choice = 1;
                     cout << "-----------------------------------" << endl;
                     cout << "Treatment menu:" << endl;
                     while (treatment_choice != 0) {
                         cout << "Medical card-1\nAdd recipe-2\nAdd referral-3\nAdd health problems-4\nDelete health problems-5\nFinish treatment-6\n";
                         treatment_choice = correct_input(0,6);
                         cout << "-----------------------------------" << endl;
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
                             cin.ignore();
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
                         case 4:{
                                 vector<string> healthProblems;
                                 string temp = "\0";
                                 cout << "-----------------------------------" << endl;
                                 cout << "Insert patient's health problems which you've detected or \"stop\" finish" << endl;
                                 cin.ignore();
                                 while (true) {
                                     cout << "Problem: " ;
                                     getline(cin, temp);
                                     if (temp == "stop") break;
                                     healthProblems.push_back(temp);
                                     user.add_health_problems(pat_id, healthProblems);
                                 }
                                 break;
                             }
                          case 5:{
                                 vector<string> curedHealthProblems;
                                 string temp = "\0";
                                 cout << "-----------------------------------" << endl;
                                 cout << "Erase patient's problems whish were cured or \"stop\" finish" << endl;
                                 cin.ignore();
                                 while (true) {
                                     cout << "Problem: " ;
                                     getline(cin, temp);
                                     if (temp == "stop") break;
                                     curedHealthProblems.push_back(temp);
                                     user.remove_health_problems(pat_id, curedHealthProblems);
                                 }
                                 break;
                             }
                         case 6:
                             user.finish_treatment(pat_id);
                             break;
                        default:
                            cout<<"Try again\n";
                         }
                     }
                 }
                 break;
             case 2:
                 user.getShedule().show_table();
                 cout << "-----------------------------------" << endl;
                 break;
            default:
                cout<<"Try again\n";
             }
         }
     }
}

void pharmacist_working_loop(int pos) {
    int choice = 1;
    while (choice != 0) {
        cout << "-----------------------------------" << endl;
        cout << "Exit-0\nCheck recipe-1\n";
        choice = correct_input(0,1);
        if (choice == 1) {

             int pat_id;
             cout << "Insert the patient id: ";
             pat_id = correct_id(1, "No patients with such ID.");
            
             pharmacists[pos].show_recipe(pat_id);
        }
    }
 }

void main_loop() {
     int c = -1;
     while (c != 0) {
         cout << "exit-0\nregister-1\nlog in-2\nset time-3\n";
         cout << "-----------------------------------" << endl;
         c = correct_input(0, 3);
         if (c == 1) {
             register_user();
             cout << "-----------------------------------" << endl;
         }
         if (c == 2) {
             string res = authorize();
             if (res == "\n") cout << "Invalid password!\n";
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
