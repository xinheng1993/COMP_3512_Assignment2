#pragma once
#include <string>
#include <iomanip>

using namespace std;


class patient {
//protected:
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
public:
	patient(){}
	patient(string _first, string _middle, string _last, 
		int _year, int _month, int _day,int _phn, int _hour, int _minute,
		string _symptoms) {
		first = _first;
		middle = _middle;
		last = _last;
		year = _year;
		month = _month;
		days = _day;
		phn = _phn;
		hour = _hour;
		minute = _minute;
		symptoms = _symptoms;
	}
	patient(const patient& other) {
		first = other.first;
		middle = other.middle;
		last = other.last;
		year = other.year;
		month = other.month;
		days = other.days;
		phn = other.phn;
		hour = other.hour;
		minute = other.minute;
		symptoms = other.symptoms;
	}
	~patient() {}
	virtual void print() const {
		cout << "<name>: " << first << " " << middle << " " << last
			<< " <health number>:" << setw(8) << setfill('0') << phn
			<< " <admission time>: " << setw(2) << setfill('0') << hour
			<< ":" << setw(2) << setfill('0') << minute << endl;
	};
};
