#include "ER.h"

#define BIG_MONTH_DAY 31
#define LINE_OFFSET 13
#define SMALL_MONTH_DAY 30
#define LEAP_YEAR_FEB 29
#define NON_LEAP_YEAR_FEB 28
#define FIRST_DAY 1
#define TOTAL_MINUTES_PER_DAY 1140

//home page of the Er system which has 6 options:
//selection 1: add new patient
//selection 2: get next patient
//selection 3: change patient
//selection 4: save patient list
//selection 5: load patient list
//selection 6: print patient list
//selection 0: exit system (will not save the file)
//pre:
//post:
//return:
void Er::home_page() {
	update_queue();
	double choose;
	system("cls");
	cout << "\n----------Queue of ER patients System----------" << endl;
	cout << "\t    " << "1.Add new patient" << endl;
	cout << "\t    " << "2.Get next patient" << endl;
	cout << "\t    " << "3.Change patient category" << endl;
	cout << "\t    " << "4.Save patient list" << endl;
	cout << "\t    " << "5.Load patient list" << endl;
	cout << "\t    " << "6.Print patient list" << endl;
	cout << "\t    " << "0.Exit program" << endl;
	cout << "please enter 0~6 to select" << endl;
	cout << "Seletc: ";
	cin >> choose;
	check_page_choose(choose, 6, 0);
	switch ((int)(choose)) {
	case 1:
		add_patients();
		break;
	case 2:
		get_next_patient();
		back_home(choose);
		break;
	case 3:
		change_category();
		break;
	case 4:
		save_to_file();
		retry_home(false);
		break;
	case 5:
		load_patients_list();
		retry_home(false);
		break;
	case 6:
		print_patient();
		back_home(choose);
		break;
	case 0:
		exit(1);
		break;
	default:
		retry_home(true);
		break;
	}
}

//category page of the Er system which has 6 options:
//when ask for a patient's category
//need to choose the category
//pre:
//post:
//return:
string Er::category_page() {
	double choose;
	//system("cls");
	cout << "\n----------Enter the category for the patient----------" << endl;
	cout << "\t\t" << "0.Critical and life - threatening, requires immediate care" << endl;
	cout << "\t\t" << "1.Critical, requires care very soon" << endl;
	cout << "\t\t" << "2.Serious, requires care soon" << endl;
	cout << "\t\t" << "3.Serious" << endl;
	cout << "\t\t" << "4.Non - serious" << endl;
	cout << "\t\t" << "5.Not a priority" << endl;
	cout << "please enter 0~5 to select" << endl;
	cout << "Seletc: ";
	cin >> choose;

	check_page_choose(choose, 5, 0);
	switch (static_cast<int>(choose))
	{
	case 0:
		return s.categorys[0];
		break;
	case 1:
		return s.categorys[1];
		break;
	case 2:
		return s.categorys[2];
		break;
	case 3:
		return s.categorys[3];
		break;
	case 4:
		return s.categorys[4];
		break;
	case 5:
		return s.categorys[5];
		break;
	default:
		cout << "error, please retry!";
		return category_page();
		break;
	}
}

//reopen the hopage after 3 second when too much invalid input
//reflash current screen
//pre:
//post:
//param is_error: to determin if is caused by invalid input
//return:
void Er::retry_home(bool is_error) {
	cin.clear();
	cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
	if (is_error) {
		cout << "Too many invalid selections, System restart at:" << endl;
	}
	else {
		cout << setw(31) << setfill('*') << "" << endl;
		cout << "*return Home Page in 3 seconds*" << endl;
		cout << setw(31) << setfill('*') << "" << endl;
	}
	for (int i = 3; i >= 1; --i) {
		cout << i << endl;
		this_thread::sleep_for(chrono::seconds(1));
	}
	home_page();
}

//go back to home page when some operation finished
//need to enter 0 to back to home
//pre:
//post:
//param: zero to check whether the user enter a 0 or not
//return:
void Er::back_home(double & zero)
{
	print_border(28);
	cout << "press 0 to return to page: ";
	cin >> zero;
	while (cin.fail() || zero != (int)zero || zero != 0) {
		print_border(27);
		cout << "*Invalid, please try again* " << endl;
		print_border(27);
		cout << "press 0 to return to page: ";
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		cin >> zero;
	}
	home_page();
}

//add new patient to the list and sort by category from 0 ~ 5
//if same category sort by admin time
//pre:
//post:
//param:
//return:
void Er::add_patients() {
	string first, middle, last, symptoms, category;
	int year, month, days, phn, hour, minute;

	enter_first_name(first);
	enter_middle_name(middle);
	enter_last_name(last);
	enter_birth_date(year, month, days);
	enter_personal_health_number(phn);
	initialize_admin_time(hour, minute);
	enter_symptoms(symptoms);
	choose_category(category);

	erPatient temp(first, middle, last, year, month, days, phn, hour, minute, symptoms, category);

	patients.push_back(temp);
	sort_patients();
	print_border(21);
	cout << "*Add patients sucess*" << endl;
	print_border(21);
	retry_home(false);
}

// prints next patient in the queue and remove it.
//PRE:	  patient list must not empty
//POST:   the next patient must be removed from the list.
//PARAM:  None.
//RETURN: None.
void Er::get_next_patient() {
	if (!patients.empty()) {
		patients.front().print();
		patients.pop_front();
	}
	else {
		print_border(27);
		cout << "*There is no more patients*" << endl;
		print_border(27);
	}

}

void Er::change_category()
{
	if (patients.empty()) {
		print_border(23);
		cout << "*There is no patients *" << "\n" << "*please check you list*" << "\n"
			<< "*or load file first!  *" << endl;
		print_border(23);
		retry_home(false);
	}
	else {
		print_patient();
		print_border(83);
		cout << "*Please enter the patient's personal health number that you would like to change.*" << endl;
		print_border(83);
		int phn_to_change;
		cin >> phn_to_change;
		check_input_integer(0, 99999999, phn_to_change);
		find_patient(phn_to_change);
	}
}

//save patients list to patients.txt file
//save patients' info and status line by line
//PRE:	  
//POST:   patients' status saved in patients file with 13 lines / patient
//PARAM:  None.
//RETURN: None.
void Er::save_to_file() {
	ofstream fout("patients.txt");
	for (auto it = patients.begin(); it != patients.end(); ++it) {
		fout << (*it).get_first() << "\n"
			<< (*it).get_middle() << "\n"
			<< (*it).get_last() << "\n"

			<< (*it).get_birthday() << "\n"

			<< setw(8) << setfill('0') << (*it).get_phn() << "\n"

			<< (*it).get_adminDate() << "\n"
			// write hr and min(no change)
			<< setw(2) << setfill('0') << (*it).get_display_hour() << "\n"
			<< setw(2) << setfill('0') << (*it).get_display_minute() << "\n"

			<< (*it).get_updated_adminDate() << "\n"
			//  hr and min(need to change)
			<< setw(2) << setfill('0') << (*it).get_hour() << "\n"
			<< setw(2) << setfill('0') << (*it).get_minute() << "\n"
			
			//
			<< (*it).get_symptoms() << "\n"
			<< (*it).get_category() << "\n";
	}
	fout.close();
}

// load the file
//PRE:	  
//POST:   all the patients are copied to current list
//PARAM:  None.
//RETURN: None.
void Er::load_patients_list() {
	if (load_file()) {
		print_border(13);
		cout << "*load Sucess*" << endl;
		print_border(13);
	}
	else {
		print_border(35);
		cout << "*load faild, please check you file*" << endl;
		print_border(35);
	}
}

// prints all patients in the queue.
//PRE:	  patient list must not empty
//POST:   
//PARAM:  None.
//RETURN: None.
void Er::print_patient() {
	if (patients.empty()) {
		print_border(23);
		cout << "*There is no patients *" << "\n" << "*please check you list*" << "\n"
			<< "*or load file first!  *" << endl;
		print_border(23);
	}
	else {
		int i = 0;
		for (auto it = patients.begin(); it != patients.end(); ++it) {
			cout << ++i << ".";
			(*it).print();
		}
	}
}

// return an int corsponding to the category.
//PRE:    None
//POST:	  None
//PARAM:  category's name
//RETURN: category number as int
int Er::get_cate_num(string cate_name) {
	if (cate_name.compare("Serious, requires care soon") == 0) {
		return 2;
	}
	else if (cate_name.compare("Serious") == 0) {
		return 3;
	}
	else if (cate_name.compare("Non - serious") == 0) {
		return 4;
	}
	else {
		return 5;
	}
}

// ask user to enter patient first name
//PRE:	  
//POST:   
//PARAM:  None.
//RETURN: None.
void Er::enter_first_name(string & first)
{
	cout << "first name: ";
	cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
	getline(cin, first);
}

// ask user to enter patient middle name
//PRE:	  
//POST:   
//PARAM:  None.
//RETURN: None.
void Er::enter_middle_name(string & middle)
{
	cout << "middle name (No middle name press Enter): ";
	getline(cin, middle);
}

// ask user to enter patient last name
//PRE:	  
//POST:   
//PARAM:  None.
//RETURN: None.
void Er::enter_last_name(string & last)
{
	cout << "last name: ";
	getline(cin, last);
}

// ask user to enter patient birth date
//PRE:	  
//POST:   
//PARAM:  None.
//RETURN: None.
void Er::enter_birth_date(int& year, int& month, int & days)
{
	cout << "birth of the year: ";
	cin >> year;
	check_input_integer(0, 9999, year);

	cout << "birth of the month: ";
	cin >> month;
	check_input_integer(1, 12, month);

	cout << "birth of the day: ";
	cin >> days;
	check_input_days(year, month, days);
}

// ask user to enter patient personal health number
//PRE:	  
//POST:   
//PARAM:  None.
//RETURN: None.
void Er::enter_personal_health_number(int & phn)
{
	cout << "personal healthcare number: ";
	cin >> phn;
	check_input_integer(0, 99999999, phn);
	check_phn(phn);
}

// initialize admin time with current local time
//PRE:	  
//POST:   
//PARAM:  None.
//RETURN: None.
void Er::initialize_admin_time(int & hour, int & minute)
{
	time_t now = time(0);
	tm *ltm = localtime(&now);
	cout << "admission time[HH:MM]: ";
	hour = ltm->tm_hour;
	minute = ltm->tm_min;
	cout << "[" << setw(2) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << "]" << "\n";
}

// ask user to enter patient's symptoms
//PRE:	  
//POST:   
//PARAM:  None.
//RETURN: None.
void Er::enter_symptoms(string & symptoms)
{
	cout << "symptoms: ";
	getline(cin, symptoms);
}

// ask user to choose patient's symptoms
//PRE:	  
//POST:   call category_page() to make a choice
//PARAM:  None.
//RETURN: None.
void Er::choose_category(string & category)
{
	category = category_page();
}

//Sort the patient list base on their catrgory, if category is the same
//first come first serve.
//PRE:    patient list cannot be empty
//POST:	  patient list is sorted
//PARAM:  None
//RETURN: None
void Er::sort_patients() {
	sort(patients.begin(), patients.end(), [=](erPatient a, erPatient b) {
		int x, y;
		if (a.get_category() != b.get_category()) {
			x = (int)distance(s.categorys, find(s.categorys, s.categorys + 6, a.get_category()));
			y = (int)distance(s.categorys, find(s.categorys, s.categorys + 6, b.get_category()));
		}
		else if (a.get_adminDate() != b.get_adminDate()) {
			return (a.get_adminDate() < b.get_adminDate());
		}
		else if (a.get_hour() != b.get_hour()) {
			x = a.get_hour();
			y = b.get_hour();
		}
		else if (a.get_minute() != b.get_minute()) {
			x = a.get_minute();
			y = b.get_minute();
		}
		return (x < y);
	});
}

//find sepecific patient by its personal health number
//PRE:   None
//POST:  None
//PARAM: the patient's personal health number 
//RETURN: None
void Er::find_patient(int patient_phn)
{
	for (auto it = patients.begin(); it != patients.end(); ++it) {
		if ((*it).get_phn() == patient_phn) {
			print_border(50);
			cout << "*Please enter new category number for this patient*" << endl;
			print_border(50);
			(*it).set_cate(category_page());
			sort_patients();
			retry_home(false);
			return;
		}
	}
	system("cls");
	print_border(65);
	cout << "*Sorry, the personal health number you entered may not correct.* \n"
		<< "Please try again.\n" << endl;
	print_border(65);
	change_category();
}

//check if patients are qulifiy to promotion their priority
//PRE:   None
//POST:  None
//PARAM: None
//RETURN: None
void Er::update_queue()
{
	if (!patients.empty()) {
		get_non_critical();
	}
}

//calculates non critical patients
//PRE:   None
//POST:  None
//PARAM: None 
//RETURN: None
void Er::get_non_critical() {
	// 2. filter list find non critical
	for (auto it = patients.begin(); it != patients.end(); ++it) {
		if ((*it).get_category().find("Critical") == string::npos) {
			promo_cate(*it);
		}
	}
}

//calculate patient's waiting time
//PRE:   admin_data less or equal than current_date (same as hour and minute)
//POST:  None
//PARAM: admintion date
//PARAM: admintion hour
//PARAM: admintion minute
//RETURN:time differnce in minutes
int Er::compare_date(Date& updated_admin_date, int admin_hr, int admin_min) {
	//4. compare date
	//int admin_year = admin_date.get_year();
	//int admin_mon = admin_date.get_month();
	//int admin_day = admin_date.get_day();
	// set time now
	time_t now = time(0);
	tm *ltm = localtime(&now);
	int current_hour = ltm->tm_hour;
	int current_minute = ltm->tm_min;
	int current_year = ltm->tm_year + 1900;
	int current_mon = ltm->tm_mon + 1;
	int current_day = ltm->tm_mday;
	Date current_date(current_year, current_mon, current_day);
	// total time in minutes
	int total_admin_min = admin_hr * 60 + admin_min;
	int total_current_min = current_hour * 60 + current_minute;

	if (updated_admin_date == current_date) {
		return total_current_min - total_admin_min;
	}
	else {
		int days_passed{ 0 };
		while (updated_admin_date != current_date) {
			++updated_admin_date;
			++days_passed;
		}
		int minutes_passed = days_passed * TOTAL_MINUTES_PER_DAY;
		return minutes_passed + total_current_min - total_admin_min;
	}
	//if (admin_year == current_year) {
	//	if (admin_mon == current_mon) {
	//		if (admin_day == current_day) {
	//			return total_current_min - total_admin_min;
	//		}
	//		else { // diff day
	//			int diff_day = current_day - admin_day;
	//			total_current_min += 24 * diff_day * 60;
	//			return total_current_min - total_admin_min;
	//		}
	//	}
	//	else { //diff month
	//		total_current_min += current_mon * 24 * 60;
	//		total_admin_min += admin_mon * 24 * 60;
	//		return total_current_min - total_admin_min;
	//	}
	//}
	//else {
	//	total_current_min += current_year * 24 * 60;
	//	total_admin_min += admin_year * 24 * 60;
	//	return total_current_min - total_admin_min;
	//}
}

//promote patient's category, if they meet criteria.
//PRE:   patient must not in critical category
//POST:	 None
//PARAM: a ref of non critical patient
//RETURN:None
void Er::promo_cate(erPatient& temp) {
	//3. find sepecific 
	//get sepecific promotion rule
	int cate_num = get_cate_num(temp.get_category());
	Date updated_adminDate = temp.get_updated_adminDate();
	int admin_hr = temp.get_hour();
	int admin_min = temp.get_minute();
	// update admin time
	// set time now
	time_t now = time(0);
	tm *ltm = localtime(&now);
	int hour = ltm->tm_hour;
	int minute = ltm->tm_min;
	//int year = ltm->tm_year + 1900;
	//int mon = ltm->tm_mon + 1;
	//int day = ltm->tm_mday;
	int diff = compare_date(updated_adminDate, admin_hr, admin_min);
	switch (cate_num)
	{
	case 2:
		if (diff >= 60) {
			//1hr
			temp.set_cate(s.categorys[cate_num - 1]);
			break;
		}
	case 3:
		if (diff >= 180) {
			//3hr
			temp.set_cate(s.categorys[cate_num - 2]);
			break;
		}
		else if (diff >= 120) {
			// 2hrs
			temp.set_cate(s.categorys[cate_num - 1]);
			break;
		}
	case 4:
		if (diff >= 360) {
			// 6 hr
			temp.set_cate(s.categorys[cate_num - 3]);
			break;
		}
		else if (diff >= 300) {
			// 5hr
			temp.set_cate(s.categorys[cate_num - 2]);
			break;
		}
		else if (diff >= 180) {
			// 3hr
			temp.set_cate(s.categorys[cate_num - 1]);
			break;
		}
	case 5:
		if (diff >= 600) {
			// 10 hr
			temp.set_cate(s.categorys[cate_num - 4]);
			break;
		}
		else if (diff >= 540) {
			// 9hr
			temp.set_cate(s.categorys[cate_num - 3]);
			break;
		}
		else if (diff >= 420) {
			// 7 hr
			temp.set_cate(s.categorys[cate_num - 2]);
			break;
		}
		else if (diff >= 240) {
			// category 5, 4hr 
			temp.set_cate(s.categorys[cate_num - 1]);
			break;
		}
	}
	//temp.set_updated_adminDate(year, mon, day);
	temp.set_hour(hour);
	temp.set_minute(minute);
	
}

// load patients list to current list and replace it 
//PRE:	  
//POST:   call category_page() to make a choice
//PARAM:  None.
//RETURN: None.
bool Er::load_file(){
	ifstream fin("patients.txt");
	vector<double> data;
	if (!fin.good()) {
		print_border(18);
		cout << "*cannot open file*" << endl;
		print_border(18);
		return false;
	}
	else {
		string buffer;
		vector<string> temp;
		while (getline(fin, buffer)) {
			temp.push_back(buffer);
		}
		int number_of_patients = (int)temp.size() / LINE_OFFSET;

		string first, middle, last, symptoms, category;
		int year, month, days, phn,
			ad_year, ad_mon, ad_day, dis_hr, dis_min,
			updated_ad_year, updated_ad_mon, updated_ad_day, hour, minute;
		patients.clear();
		string date, admin_date, updated_admin_date;
		for (int i = 0; i < number_of_patients; ++i) {
			first = temp.at(i * LINE_OFFSET + 0);
			middle = temp.at(i * LINE_OFFSET + 1);
			last = temp.at(i * LINE_OFFSET + 2);

			date = temp.at(i * LINE_OFFSET + 3);
			replace(date.begin(), date.end(), '/', ' ');
			istringstream iss(date);
			iss >> year;
			iss >> month;
			iss >> days;

			phn = stoi(temp.at(i * LINE_OFFSET + 4));

			admin_date = temp.at(i * LINE_OFFSET + 5);
			replace(admin_date.begin(), admin_date.end(), '/', ' ');
			istringstream ad_iss(admin_date);
			ad_iss >> ad_year;
			ad_iss >> ad_mon;
			ad_iss >> ad_day;
			// load display hr and min
			dis_hr = stoi(temp.at(i * LINE_OFFSET + 6));
			dis_min = stoi(temp.at(i * LINE_OFFSET + 7));

			updated_admin_date = temp.at(i * LINE_OFFSET + 8);
			replace(updated_admin_date.begin(), updated_admin_date.end(), '/', ' ');
			istringstream update_ad_iss(updated_admin_date);
			update_ad_iss >> updated_ad_year;
			update_ad_iss >> updated_ad_mon;
			update_ad_iss >> updated_ad_day;
			hour = stoi(temp.at(i * LINE_OFFSET + 9));
			minute = stoi(temp.at(i * LINE_OFFSET + 10));
			
			symptoms = temp.at(i * LINE_OFFSET + 11);
			category = temp.at(i * LINE_OFFSET + 12);
			erPatient temp_patient(first, middle, last, year, month, days, phn, hour, minute, symptoms, category);
			temp_patient.set_adminDate(ad_year, ad_mon, ad_day);

			temp_patient.set_display_hour(dis_hr);
			temp_patient.set_display_minute(dis_min);

			patients.push_back(temp_patient);

		}
		return true;
	}
	fin.close();
}

// check the user input for the date
//PRE:	  
//POST:   
//PARAM:  None.
//RETURN: None.
void Er::check_input_days(int & year, int & month, int & days){
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10
		|| month == 12) {
		check_input_integer(1, 31, days);
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11) {
		check_input_integer(FIRST_DAY, SMALL_MONTH_DAY, days);
	}
	else if (month == 2) {
		if (year % 100 != 0) {
			if (year % 4 == 0) {
				check_input_integer(FIRST_DAY, LEAP_YEAR_FEB, days);
			}
			else {
				check_input_integer(FIRST_DAY, NON_LEAP_YEAR_FEB, days);
			}
		}
		else {
			if (year % 400 == 0) {
				check_input_integer(FIRST_DAY, LEAP_YEAR_FEB, days);
			}
			else {
				check_input_integer(FIRST_DAY, NON_LEAP_YEAR_FEB, days);
			}
		}
	}
}

// check the user integer input
//PRE:	  
//POST:   
//PARAM:  lower the lower bound of the input range.
//PARAM:  upper the upper bound of the input range.
//PARAM:  value the value which need to store the input
//RETURN: None.
void Er::check_input_integer(int lower, int upper, int& value){
	while (cin.fail() || value > upper || value < lower) {
		cout << "Invalid value please try again: ";
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		cin >> value;
	}
	cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
}

//check if personal health number is already in use.
// if it's in use then ask for enter again.
//PRE:   None
//POST:  None
//PARAM: personal health number
//RETURN: None
void Er::check_phn(int& phn) {
	while (check_if_phn_exist(phn)) {
		print_border(39);
		cout << "*personal health number already exsits*" << endl;
		print_border(39);
		cout << "please try again: ";
		cin.clear();
		cin >> phn;
	}
}

// check if personal health number is already in use.
// if it's in use then ask for enter again.
//PRE:   None
//POST:  None
//PARAM: personal health number
//RETURN: true if the phn is already in use, otherwise, return false.
bool Er::check_if_phn_exist(int& val) {
	for (auto it = patients.begin(); it != patients.end(); ++it) {
		if (val == (*it).get_phn())
			return true;
	}
	return false;
}

// check the user choic for each page
//PRE:	  
//POST:   
//PARAM:  lower the lower bound of the input range.
//PARAM:  upper the upper bound of the input range.
//PARAM:  choose the choic which user made
//RETURN: None.
void Er::check_page_choose(double& choose, int upper,int lower) {
	while (cin.fail() || choose != (int)choose || choose > upper || choose < lower) {
		cout << "Invalid selection, please try again: ";
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		cin >> choose;
	}
}

// print border for each message the system output
//PRE:	  
//POST:   
//PARAM: 
//RETURN: None.
void Er::print_border(int number){
	cout << setw(number) << setfill('*') << "" << endl;
}
