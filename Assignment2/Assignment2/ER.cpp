#include "ER.h"

void Er::add(){
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
	cin.ignore();
	getline(cin, first);

	cout << "middle name (if no middle name please enter NULL): ";
	cin.ignore();
	getline(cin, middle);

	cout << "last name: ";
	cin.ignore();
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

	cout << "admission hour: ";
	cin >> hour;
	check_input_integer(0, 23, hour);

	cout << "admission minutes: ";
	cin >> minute;
	check_input_integer(0, 59, minute);

	cout << "symptoms: ";
	cin.ignore();
	getline(cin, symptoms);

	category_page(category);
	
	erPatient temp(first, middle, last, year, month, days, phn, hour, minute, symptoms, category);
	patients.push_back(temp);
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
	cout << setw(12) << "" << "1.Add new patient" << endl;
	cout << setw(12) << "" << "2.Get next patient" << endl;
	cout << setw(12) << "" << "3.Change patient category" << endl;
	cout << setw(12) << "" << "4.Save patient list" << endl;
	cout << setw(12) << "" << "5.Load patient list" << endl;
	cout << setw(12) << "" << "6.Print patient list" << endl;
	cout << setw(12) << "" << "0.Exit program" << endl;
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
	switch (static_cast<int>(choose))
	{
	case 1:
		add();
		break;
	case 2:

		break;
	case 3:

		break;
	case 4:
		save_to_file();
		break;
	case 5:
		if (load_file()) {
			home_page();
		}
		break;
	case 6:
		print_patient();
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
	cout << setw(16) << "" << "0.Critical and life - threatening, requires immediate care" << endl;
	cout << setw(16) << "" << "1.Critical, requires care very soon" << endl;
	cout << setw(16) << "" << "2.Serious, requires care soon" << endl;
	cout << setw(16) << "" << "3.Serious" << endl;
	cout << setw(16) << "" << "4.Non - serious" << endl;
	cout << setw(16) << "" << "5.Not a priority" << endl;
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

void Er::save_to_file(){
	ofstream fout("patients.txt");
	for (auto it = patients.begin(); it != patients.end(); ++it) {
		fout << (*it).get_first() << "\n"
			<< (*it).get_middle() << "\n"
			<< (*it).get_last() << "\n"
			<< (*it).get_year() << "\n"
			<< (*it).get_month() << "\n"
			<< (*it).get_days() << "\n"
			<< (*it).get_phn() << "\n"
			<< (*it).get_hour() << "\n"
			<< (*it).get_minute() << "\n"
			<< (*it).get_symptoms() << "\n"
			<< (*it).get_category() << "\n";
	}
	fout.close();
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
