#pragma once
#include "Menu.h"
#include"Category.h"
#include<vector>
#include <iostream>
#include "erPatient.h"
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <queue>
using namespace std;
class menu;
class Er : public menu{
	deque<erPatient> patients;
	Category s;
public:
	Er() {}
	
	virtual void retry_home(bool is_error) override;
	virtual void home_page() override;
	virtual string category_page() override;
	void system_start() {home_page();}

	void add_patients();
	void sort_patients();
	void get_next_patient();
	void print_patient();
	void save_to_file();
	bool load_file();
	void change_category();
	void back_home(double &zero);
	erPatient& find_patient(int patient_phn);
	void check_input_days(int& year, int& month, int& days);
	void check_input_integer(int lower, int upper, int& value);
	void check_phn(int& phn);
	bool check_exits(int& val);
	void check_page_choose(double& choose, int upper, int lower);
	void print_border(int number);
};