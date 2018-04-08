#pragma once
#include"Menu.h"
#include"Patient.h"
#include"Category.h"
#include<vector>
#include<iostream>
using namespace std;

class Er {
	vector<patient> patients;
	menu er_menu;
	category er_category;
public:
	Er() {}
	void add() {
		string first;
		string middle;
		string last;
		int year;
		int month;
		int days;
		int phn;
		int hour;
		int minute;
		string symptoms;
		string category;
		cout << "please enter: " << endl;

		cout << "first name: ";
		cin >> first;
		cout << "\n";

		cout << "middle name: (if no middle name please enter NULL)";
		cin >> middle;
		cout << "\n";

		cout << "last name: ";
		cin >> last;
		cout << "\n";

		cout << "birth of the year: ";
		cin >> year;
		check_input_integer(0, 9999, year);

		cout << "birth of the month: ";
		cin >> month;
		check_input_integer(1, 12, month);

		cout << "birth of the day: ";
		cin >> days;
		check_input_days(year, month, days);

		cout << "personal healthcare number: ";
		cin >> phn;
		check_input_integer(0, 99999999, phn);

		cout << "admission hour: ";
		cin >> hour;
		check_input_integer(0, 24, hour);

		cout << "admission minutes: ";
		cin >> minute;
		check_input_integer(0, 60, minute);

		cout << "symptoms";
		cin >> symptoms;
		cout << "\n";

		cout << "category";




		//patients.push_back()
	}


	void check_input_days(int& year, int& month,int& days) {
		if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10
			|| month == 12) {
			check_input_integer(1, 31, days);
		}
		else if (month == 4 || month == 6 || month == 9 || month == 11) {
			check_input_integer(1, 30, days);
		}
		else if (month == 2) {
			if (year % 100 != 0) {
				if (year % 4 == 0) {
					check_input_integer(1, 29, days);
				}
				else {
					check_input_integer(1, 28, days);
				}
			}
			else {
				if (year % 400 == 0) {
					check_input_integer(1, 29, days);
				}
				else {
					check_input_integer(1, 28, days);
				}
			}
		}
	}

	void check_input_integer(int lower, int upper, int& value) {
		while (cin.fail() || value >= upper || value <= lower) {
			cout << "Invalid value please try again: ";
			cin.clear();
			cin.ignore();
			cin >> value;
		}
		cout << "\n";
	}
};