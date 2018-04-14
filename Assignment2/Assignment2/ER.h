#pragma once
#include <algorithm>
#include "Category.h"
#include "erPatient.h"
#include <fstream>
#include <iostream>
#include "Menu.h"
#include <queue>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Er : public menu{
	deque<erPatient> patients;
	Category s;
public:
	Er() {}
	virtual void home_page() override;
	virtual string category_page() override;
	virtual void retry_home(bool is_error) override;
	void back_home(double &zero);

	//start system
	void system_start() {home_page();}

	//home page menu
	void add_patients();
	void get_next_patient();
	void change_category();
	void save_to_file();
	void load_patients_list();
	void print_patient();

	//add_patients related function
	void enter_first_name(string& first);
	void enter_middle_name(string& middle);
	void enter_last_name(string& last);
	void enter_birth_days(int& year, int& month, int & days);
	void enter_personal_number(int& phn);
	void initialize_admin_time(int& hour, int& minute);
	void enter_symptoms(string& symptoms);
	void choose_category(string& category);
	void sort_patients();

	//change_category related function
	void find_patient(int patient_phn);

	//promotion process
	void update_queue();
	void get_non_critical();
	int get_cate_num(string);
	bool compare_date(Date admin_date, int admin_hr, int admin_min, int promo_min);
	void promo_cate(erPatient& temp);
	
	//load patients list
	bool load_file();


	//check input functions
	void check_input_days(int& year, int& month, int& days);
	void check_input_integer(int lower, int upper, int& value);
	void check_phn(int& phn);
	bool check_exits(int& val);
	void check_page_choose(double& choose, int upper, int lower);
	void print_border(int number);
};