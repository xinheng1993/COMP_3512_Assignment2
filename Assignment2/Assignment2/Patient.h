#pragma once
#include <string>
#include <iomanip>
#include "Date.h"
using namespace std;


class patient {
	string first, middle, last, symptoms;
	int year, month, days, phn, hour, minute;
	Date birthday;
	
public:
	patient(){}
	patient(string _first, string _middle, string _last, 
		int _year, int _month, int _day,int _phn, int _hour, int _minute,
		string _symptoms) {
		first = _first;
		middle = _middle;
		last = _last;
		Date temp(_year, _month, _day);
		birthday = temp;
		phn = _phn;
		hour = _hour;
		minute = _minute;
		symptoms = _symptoms;
	}
	patient(const patient& other) {
		first = other.first;
		middle = other.middle;
		last = other.last;
		birthday = other.birthday;
		phn = other.phn;
		hour = other.hour;
		minute = other.minute;
		symptoms = other.symptoms;
	}
	~patient() {}

	string get_first() const {
		return first;
	}
	string get_middle() const {
		return middle;
	}
	string get_last() const {
		return last;
	}
	Date get_birthday() const {
		return birthday;
	}
	int get_phn() const {
		return phn;
	}
	int get_hour() const {
		return hour;
	}
	int get_minute() const {
		return minute;
	}
	string get_symptoms() const{
		return symptoms;
	}
	virtual void print() const {
		cout << "<name>: " << first << " " << middle << " " << last << "\n"
			<< "   <health number>:" << setw(8) << setfill('0') << phn <<"\n"
			<< "   <admission time>: " << setw(2) << setfill('0') << hour
			<< ":" << setw(2) << setfill('0') << minute << endl;
	};
};
