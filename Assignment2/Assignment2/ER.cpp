#include "ER.h"

void Er::add_patients(){
	time_t now = time(0);
	tm *ltm = localtime(&now);

	string first, middle, last, symptoms, category;
	int year, month, days, phn, hour, minute;

	cout << "first name: ";
	cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
	getline(cin, first);

	cout << "middle name (No middle name press Enter): ";
	getline(cin, middle);

	cout << "last name: ";
	getline(cin, last);

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
	check_phn(phn);

	cout << "admission time(HH:MM): ";
	hour = ltm->tm_hour;
	minute = ltm->tm_min;
	cout <<"<"<< hour << ":" << minute <<">"<< "\n";


	cout << "symptoms: ";
	getline(cin, symptoms);

	category_page(category);
	
	erPatient temp(first, middle, last, year, month, days, phn, hour, minute, symptoms, category);
	patients.push_back(temp);
	sort_patients();
	retry_home(false);
}

void Er::retry_home(bool is_error){
	cin.clear();
	cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
	if (is_error) {
		cout << "Too many invalid selections, System restart at:" << endl;
	}
	else {
		cout << "return Home Page in 3 seconds:" << endl;
	}
	for (int i = 3; i >= 1; --i) {
		cout << i << endl;
		this_thread::sleep_for(chrono::seconds(1));
	}
	home_page();
}

void Er::retry_category(string & category){
	cin.clear();
	cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
	cout << "Too many invalid selections, category page will be reloaded at:" << endl;
	for (int i = 3; i >= 1; --i) {
		cout << i << endl;
		this_thread::sleep_for(chrono::seconds(1));
	}
	category_page(category);
}

void Er::home_page(){
	double choose;
	system("cls");
	cout << "\n----------Queue of patients System----------" << endl;
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
	error_times = 0;
	while (cin.fail() || choose != (int)choose || choose > 6 || choose < 0) {
		if (error_times == 5) {
			retry_home(true);
			return;
		}
		cout << "Invalid selection, please try again: ";
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		++error_times;
		cin >> choose;
	}
	switch (static_cast<int>(choose)){
	case 1:
		add_patients();
		break;
	case 2:
		get_next_patient();
		back_home(choose);
		break;
	case 3:

		break;
	case 4:
		save_to_file();
		retry_home(false);
		break;
	case 5:
		if (load_file()) {
			cout << "load sucessful" << endl;
		}
		else {
			cout << "load faild" << endl;
		}
		retry_home(false);
		break;
	case 6:
		print_patient();
		back_home(choose);
		home_page();
		break;
	case 0:
		exit(1);
		break;
	default:
		retry_home(true);
		break;
	}
}

void Er::category_page(string & category){
	double choose;
	//system("cls");
	cout << "\n----------Enter the category for the patient----------" << endl;
	cout << "\t\t" << "0.Critical and life - threatening, requires immediate care" << endl;
	cout << "\t\t" << "1.Critical, requires care very soon" << endl;
	cout << "\t\t" << "2.Serious, requires care soon" << endl;
	cout << "\t\t" << "3.Serious" << endl;
	cout << "\t\t" << "4.Non - serious" << endl;
	cout << "\t\t" << "5.Not a priority" << endl;
	cout << "please enter 0~6 to select" << endl;
	cout << "Seletc: ";
	cin >> choose;
	error_times = 0;
	while (cin.fail() || choose != (int)choose || choose > 5 || choose < 0) {
		if (error_times == 5) {
			retry_category(category);
			return;
		}
		cout << "Invalid selection, please try again: ";
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		++error_times;
		cin >> choose;
	}
	switch (static_cast<int>(choose))
	{
	case 0:
		category = s.categorys[0];
		break;
	case 1:
		category = s.categorys[1];
		break;
	case 2:
		category = s.categorys[2];
		break;
	case 3:
		category = s.categorys[3];
		break;
	case 4:
		category = s.categorys[4];
		break;
	case 5:
		category = s.categorys[5];
		break;
	default:
		retry_category(category);
		break;
	}
}

void Er::sort_patients(){
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
			x= a.get_hour();
			y = b.get_hour();
		} 
		else if (a.get_minute() != b.get_minute()) {
			x = a.get_minute();
			y = b.get_minute();
		}
		return (x < y);
	});
}

void Er::print_patient() const{
	if (patients.empty()) {
		cout << "there is no patients: " << endl;
	}
	else {
		int i = 0;
		for (auto it = patients.begin(); it != patients.end(); ++it) {
			cout << ++i << ". ";
			(*it).print();
		}
	}
}

void Er::save_to_file(){
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
			<< (*it).get_symptoms() << "\n"
			<< (*it).get_category() << "\n";
	}
	fout.close();
}

bool Er::load_file(){
	ifstream fin("patients.txt");
	vector<double> data;
	if (!fin.good()) {
		cout << "cannot open file" << endl;
		return false;
	}
	else {
		string buffer;
		vector<string> temp;
		while (getline(fin, buffer)) {
			temp.push_back(buffer);
		}
		int number_of_patients = (int)temp.size() / 10;

		string first, middle, last, symptoms, category;
		int year, month, days, phn, hour, minute, ad_year, ad_mon, ad_day;
		patients.clear();
		string date, admin_date;
		for (int i = 0; i < number_of_patients; ++i) {
			first = temp.at(i * 10 + 0);
			middle = temp.at(i * 10 + 1);
			last = temp.at(i * 10 + 2);
			date = temp.at(i * 10 + 3);
			istringstream iss(date);
			iss >> year;
			iss >> month;
			iss >> days;
			phn = stoi(temp.at(i * 10 + 4));
			admin_date = temp.at(i * 10 + 5);
			istringstream ad_iss(admin_date);
			ad_iss >> ad_year;
			ad_iss >> ad_mon;
			ad_iss >> ad_day;
			hour = stoi(temp.at(i * 10 + 6));
			minute = stoi(temp.at(i * 10 + 7));
			symptoms = temp.at(i * 10 + 8);
			category = temp.at(i * 10 + 9);
			erPatient temp_patient(first, middle, last, year, month, days, phn, hour, minute, symptoms, category);
			temp_patient.set_adminDate(ad_year, ad_mon, ad_day);
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

void Er::check_input_integer(int lower, int upper, int& value){
	while (cin.fail() || value > upper || value < lower) {
		cout << "Invalid value please try again: ";
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		cin >> value;
	}
	cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
}

void Er::get_next_patient() {
	patients.front().print();
	patients.pop_front();
}

void Er::back_home(double & zero)
{
	cout << "press 0 to return to page: ";
	cin >> zero;
	while (cin.fail() || zero != (int)zero || zero != 0) {
		cout << "Invalid, please try again: " << endl;
		cout << "press 0 to return to page: ";
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		cin >> zero;
	}
	home_page();
}

void Er::check_phn(int& phn) {
	while (check_exits(phn)) {
		cout << "personal health number already exsits, please try again: ";
		cin.clear();
		cin >> phn;
	}
}
bool Er::check_exits(int& val) {
	for (auto it = patients.begin(); it != patients.end(); ++it) {
		if (val == (*it).get_phn())
			return true;
	}
	return false;
}