#include "Header.h"

int pick_time() {
	int choice;
	cout << "pick free time" << endl;
	cin >> choice;
	return choice - 1;
}