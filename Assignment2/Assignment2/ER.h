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
		patients.front().print();
	}

	void save_to_file();
	void check_input_days(int& year, int& month, int& days);
	void check_input_integer(int lower, int upper, int& value);
};