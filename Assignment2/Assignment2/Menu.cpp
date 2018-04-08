#include "Menu.h"
#include <thread>
#include <chrono>
#include <iomanip>
#include <string>
void menu::retry(string page)
{
	cout << "Too many invalid selections, System restart at:" << endl;
	for (int i = 3; i >= 1; --i) {
		cout << i << endl;
		this_thread::sleep_for(chrono::seconds(1));
	}
	if (page.compare("home_page")) {
		home_page();
	}
	else if(page.compare("category_page")){
		category_page();
	}
}

void menu::home_page(){
	double choose;
	system("cls");
		cout << "\n----------Queue of patients System----------" << endl;
		cout << setw(12)<<""<<"1.Add new patient" << endl;
		cout << setw(12) << ""<<"2.Get next patient" << endl;
		cout << setw(12) << ""<<"3.Change patient category" << endl;
		cout << setw(12) << ""<<"4.Save patient list" << endl;
		cout << setw(12) << "" << "5.Load patient list" << endl;
		cout << setw(12) << "" << "6.Print patient list" << endl;
		cout << setw(12) << "" << "0.Exit program" << endl;
		cout << "please enter 0~6 to select" << endl;
		cout << "Seletc: ";
		cin >> choose;
		int trys{ 0 };
		while (cin.fail() || choose!=(int)choose) {
			cout << "Invalid selection, please try again: ";
			cin.clear();
			cin.ignore();
			cin >> choose;
			++trys;
			if (trys == 5) {
				retry("home_page");
				break;
			}
		}
		switch (static_cast<int>(choose))
		{
		case 1:

			break;
		case 2:

			break;
		case 3:

			break;
		case 4:

			break;
		case 5:

			break;
		case 6:

			break;
		case 0:
			exit(1);
			break;
		default:
			retry("home_page");
			break;
		}
}

void menu::category_page() {
	double choose;
	system("cls");
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
	int trys{ 0 };
	while (cin.fail() || choose != (int)choose) {
		cout << "Invalid selection, please try again: ";
		cin.clear();
		cin.ignore();
		cin >> choose;
		++trys;
		if (trys == 5) {
			retry("category_page");
			break;
		}
	}
	switch (static_cast<int>(choose))
	{
	case 1:

		break;
	case 2:

		break;
	case 3:

		break;
	case 4:

		break;
	case 5:

		break;
	case 6:

		break;
	case 0:
		exit(1);
		break;
	default:
		retry("category_page");
		break;
	}
}
