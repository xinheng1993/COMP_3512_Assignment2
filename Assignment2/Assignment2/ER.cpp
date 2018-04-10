#include "ER.h"

void Er::add_patients(){
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

	cout << "admission hour: ";
	cin >> hour;
	check_input_integer(0, 23, hour);

	cout << "admission minutes: ";
	cin >> minute;
	check_input_integer(0, 59, minute);

	cout << "symptoms: ";
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

		break;
	case 3:

		break;
	case 4:
		save_to_file();
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
		cout << "press 0 to return to page: ";
		cin >> choose;
		while (cin.fail() || choose != (int)choose || choose != 0) {
			cout << "Invalid, please try again: " << endl;
			cout << "press 0 to return to page: ";
			cin.clear();
			cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
			cin >> choose;
		}
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

void Er::print_patient() const{
	int i = 0;
	for (auto it = patients.begin(); it != patients.end(); ++it) {
		cout << ++i << ". ";
		(*it).print();
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
		int number_of_patients = (int)temp.size() / 9;

		string first, middle, last, symptoms, category;
		int year, month, days, phn, hour, minute;
		patients.clear();
		for (int i = 0; i < number_of_patients; ++i) {
			first = temp.at(i * 9 + 0);
			middle = temp.at(i * 9 + 1);
			last = temp.at(i * 9 + 2);
			string date = temp.at(i * 9 + 3);
			istringstream iss(date);
			iss >> year;
			iss >> month;
			iss >> days;
			phn = stoi(temp.at(i * 9 + 4));
			hour = stoi(temp.at(i * 9 + 5));
			minute = stoi(temp.at(i * 9 + 6));
			symptoms = temp.at(i * 9 + 7);
			category = temp.at(i * 9 + 8);
			erPatient temp(first, middle, last, year, month, days, phn, hour, minute, symptoms, category);
			patients.push_back(temp);
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
