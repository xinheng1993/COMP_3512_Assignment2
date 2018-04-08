#include "Menu.h"
#include "ER.h"
#include <thread>
#include <chrono>
#include <iomanip>
#include <string>
void menu::retry(const char& page)
{
	cin.clear();
	cin.ignore();
	cout << "Too many invalid selections, System restart at:" << endl;
	for (int i = 3; i >= 1; --i) {
		cout << i << endl;
		this_thread::sleep_for(chrono::seconds(1));
	}
	switch (page)
	{
	case 'h':
		home_page();
		break;
	case 'c':
		category_page();
		break;
	default:
		
		break;
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
				retry('h');
				return;
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
			retry('h');
			break;
		}
}

void menu::category_page(string& category) {
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
			retry('c');
			return;
		}
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
		retry('c');
		break;
	}
}
