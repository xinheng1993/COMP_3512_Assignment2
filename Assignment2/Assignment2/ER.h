#pragma once
#include "Menu.h"
#include"Category.h"
#include<vector>
#include<iostream>
#include "erPatient.h"
#include <fstream>
#include<string>
#include<algorithm>
using namespace std;
class menu;
class Er : public menu{
	vector<erPatient> patients;
	category s;
	int error_times;
public:
	Er() { error_times = 0; }
	void add();
	virtual void retry_home(bool is_error) override;
	virtual void retry_category(string& category) override;
	virtual void home_page() override;
	virtual void category_page(string& category) override;
	void system_start() {
		home_page();
	}
	void print_patient() const {
		int i = 0;
		for (auto it = patients.begin(); it != patients.end(); ++it) {
			cout << ++i << ". ";
			(*it).print();
		}
	}

	void save_to_file();
	bool load_file() {
		ifstream fin("patients.txt");
		vector<double> data;
		if (!fin.good()) {
			cout << "cannot open file" << endl;
			return false;
		}
		else {
			string buffer;
			vector<string> temp;
			while (getline(fin,buffer)) {
				temp.push_back(buffer);
			}
			int number_of_patients = (int)temp.size() / 11;
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
			for (int i = 0; i < number_of_patients; ++i) {
				first = temp.at(i * 11 + 0);
				middle = temp.at(i * 11 + 1);
				last = temp.at(i * 11 + 2);
				year = stoi(temp.at(i * 11 + 3));
				month = stoi(temp.at(i * 11 + 4));
				days = stoi(temp.at(i * 11 + 5));
				phn = stoi(temp.at(i * 11 + 6));
				hour = stoi(temp.at(i * 11 + 7));
				minute = stoi(temp.at(i * 11 + 8));
				symptoms = temp.at(i * 11 + 9);
				category = temp.at(i * 11 + 10);
				erPatient temp(first, middle, last, year, month, days, phn, hour, minute, symptoms, category);
				patients.push_back(temp);
			}
			return true;
		}
		fin.close();
	}
	void check_input_days(int& year, int& month, int& days);
	void check_input_integer(int lower, int upper, int& value);
};