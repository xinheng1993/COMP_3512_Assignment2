#include "ER.h"

#define BIG_MONTH_DAY 31
#define LINE_OFFSET 12
#define SMALL_MONTH_DAY 30
#define LEAP_YEAR_FEB 29
#define NON_LEAP_YEAR_FEB 28
#define FIRST_DAY 1

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
	switch (static_cast<int>(choose)) {
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

void Er::add_patients() {
	string first, middle, last, symptoms, category;
	int year, month, days, phn, hour, minute;

	enter_first_name(first);
	enter_middle_name(middle);
	enter_last_name(last);
	enter_birth_days(year, month, days);
	enter_personal_number(phn);
	initialize_admin_time(hour, minute);
	choose_category(category);

	erPatient temp(first, middle, last, year, month, days, phn, hour, minute, symptoms, category);

	patients.push_back(temp);
	sort_patients();
	print_border(21);
	cout << "*Add patients sucess*" << endl;
	print_border(21);
	retry_home(false);
}

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

void Er::save_to_file() {
	ofstream fout("patients.txt");
	for (auto it = patients.begin(); it != patients.end(); ++it) {
		fout << (*it).get_first() << "\n"
			<< (*it).get_middle() << "\n"
			<< (*it).get_last() << "\n"
			<< (*it).get_birthday() << "\n"
			<< setw(8) << setfill('0') << (*it).get_phn() << "\n"
			<< (*it).get_adminDate() << "\n"
			<< setw(2) << setfill('0') << (*it).get_hour() << "\n"
			<< setw(2) << setfill('0') << (*it).get_minute() << "\n"
			// write hr and min
			<< setw(2) << setfill('0') << (*it).get_display_hour() << "\n"
			<< setw(2) << setfill('0') << (*it).get_display_minute() << "\n"
			//
			<< (*it).get_symptoms() << "\n"
			<< (*it).get_category() << "\n";
	}
	fout.close();
}

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

void Er::enter_first_name(string & first)
{
	cout << "first name: ";
	cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
	getline(cin, first);
}

void Er::enter_middle_name(string & middle)
{
	cout << "middle name (No middle name press Enter): ";
	getline(cin, middle);
}

void Er::enter_last_name(string & last)
{
	cout << "last name: ";
	getline(cin, last);
}

void Er::enter_birth_days(int& year, int& month, int & days)
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

void Er::enter_personal_number(int & phn)
{
	cout << "personal healthcare number: ";
	cin >> phn;
	check_input_integer(0, 99999999, phn);
	check_phn(phn);
}

void Er::initialize_admin_time(int & hour, int & minute)
{
	time_t now = time(0);
	tm *ltm = localtime(&now);
	cout << "admission time[HH:MM]: ";
	hour = ltm->tm_hour;
	minute = ltm->tm_min;
	cout << "[" << setw(2) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << "]" << "\n";
}

void Er::enter_symptoms(string & symptoms)
{
	cout << "symptoms: ";
	getline(cin, symptoms);
}

void Er::choose_category(string & category)
{
	category = category_page();
}

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

void Er::update_queue()
{
	if (!patients.empty()) {
		get_non_critical();
	}
}

void Er::get_non_critical() {
	// 2. filter list find non critical
	for (auto it = patients.begin(); it != patients.end(); ++it) {
		if ((*it).get_category().find("Critical") == string::npos) {
			promo_cate(*it);
		}
	}
}

bool Er::compare_date(Date admin_date, int admin_hr, int admin_min, int promo_min) {
	//4. compare date
	int admin_year = admin_date.get_year();
	int admin_mon = admin_date.get_month();
	int admin_day = admin_date.get_day();
	// set time now
	time_t now = time(0);
	tm *ltm = localtime(&now);
	int hour = ltm->tm_hour;
	int minute = ltm->tm_min;
	int year = ltm->tm_year + 1900;
	int mon = ltm->tm_mon + 1;
	int day = ltm->tm_mday;
	// total time in minutes
	int total_admin = admin_hr * 60 + admin_min;
	int total_min = hour * 60 + minute;
	if (admin_year == year) {
		if (admin_mon == mon) {
			if (admin_day == day) {
				return (total_min - total_admin >= promo_min) ? true : false;				
			}
			else { // diff day
				int diff_day = day - admin_day;
				total_min += 24 * diff_day * 60;
				return (total_min - total_admin >= promo_min) ? true : false;			
			}
		}
		else { //diff month
			total_min += mon * 24 * 60;
			total_admin += admin_mon * 24 * 60;
			return (total_min - total_admin >= promo_min) ? true : false;
		}
	}
	else {
		total_min += year * 24 * 60;
		total_admin += admin_year * 24 * 60;
		return (total_min - total_admin >= promo_min) ? true : false;
	}
}

void Er::promo_cate(erPatient& temp) {
	//3. find sepecific 
	//get sepecific promotion rule
	int cate_num = get_cate_num(temp.get_category());
	Date admin_date = temp.get_adminDate();
	int admin_hr = temp.get_hour();
	int admin_min = temp.get_minute();
	// update admin time
	// set time now
	time_t now = time(0);
	tm *ltm = localtime(&now);
	int hour = ltm->tm_hour;
	int minute = ltm->tm_min;
	int year = ltm->tm_year + 1900;
	int mon = ltm->tm_mon + 1;
	int day = ltm->tm_mday;

	switch (cate_num)
	{
	case 2:
		if (compare_date(admin_date,admin_hr,admin_min,60)) {
			temp.set_cate(s.categorys[cate_num - 1]);
			temp.set_adminDate(year, mon, day);
			temp.set_hour(hour);
			temp.set_minute(minute);
			break;
		}
		break;
	case 3:
		if (compare_date(admin_date, admin_hr, admin_min,120)) {
			temp.set_cate(s.categorys[cate_num - 1]);
			temp.set_adminDate(year, mon, day);
			temp.set_hour(hour);
			temp.set_minute(minute);
			break;
		}
		break;
	case 4:
		if (compare_date(admin_date, admin_hr, admin_min,180)) {
			temp.set_cate(s.categorys[cate_num - 1]);
			temp.set_adminDate(year, mon, day);
			temp.set_hour(hour);
			temp.set_minute(minute);
			break;
		}
		break;
	case 5:
		if (compare_date(admin_date, admin_hr, admin_min,240)) {
			temp.set_cate(s.categorys[cate_num - 1]);
			temp.set_adminDate(year, mon, day);
			temp.set_hour(hour);
			temp.set_minute(minute);
			break;
		}
		break;
	default:
		break;
	}
	
}

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
		int year, month, days, phn, hour, minute, ad_year, ad_mon, ad_day, dis_hr, dis_min;
		patients.clear();
		string date, admin_date;
		for (int i = 0; i < number_of_patients; ++i) {
			first = temp.at(i * LINE_OFFSET + 0);
			middle = temp.at(i * LINE_OFFSET + 1);
			last = temp.at(i * LINE_OFFSET + 2);
			date = temp.at(i * LINE_OFFSET + 3);
			istringstream iss(date);
			iss >> year;
			iss >> month;
			iss >> days;
			phn = stoi(temp.at(i * LINE_OFFSET + 4));
			admin_date = temp.at(i * LINE_OFFSET + 5);
			istringstream ad_iss(admin_date);
			ad_iss >> ad_year;
			ad_iss >> ad_mon;
			ad_iss >> ad_day;
			hour = stoi(temp.at(i * LINE_OFFSET + 6));
			minute = stoi(temp.at(i * LINE_OFFSET + 7));
			// load display hr and min
			dis_hr = stoi(temp.at(i * LINE_OFFSET + 8));
			dis_min = stoi(temp.at(i * LINE_OFFSET + 9));
			//
			symptoms = temp.at(i * LINE_OFFSET + 10);
			category = temp.at(i * LINE_OFFSET + 11);
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

void Er::check_input_integer(int lower, int upper, int& value){
	while (cin.fail() || value > upper || value < lower) {
		cout << "Invalid value please try again: ";
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		cin >> value;
	}
	cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
}

void Er::check_phn(int& phn) {
	while (check_phn_exits(phn)) {
		print_border(39);
		cout << "*personal health number already exsits*" << endl;
		print_border(39);
		cout << "please try again: ";
		cin.clear();
		cin >> phn;
	}
}

bool Er::check_phn_exits(int& val) {
	for (auto it = patients.begin(); it != patients.end(); ++it) {
		if (val == (*it).get_phn())
			return true;
	}
	return false;
}

void Er::check_page_choose(double& choose, int upper,int lower) {
	while (cin.fail() || choose != (int)choose || choose > upper || choose < lower) {
		cout << "Invalid selection, please try again: ";
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		cin >> choose;
	}
}

void Er::print_border(int number){
	cout << setw(number) << setfill('*') << "" << endl;
}
