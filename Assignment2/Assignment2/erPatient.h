#pragma once
#include "Patient.h"

class erPatient:public patient {
protected:
	string category;
public:
	erPatient() {}
	erPatient(string _first, string _middle, string _last,
		int _year, int _month, int _day, int _phn, int _hour, int _minute,
		string _symptoms,string _category):patient(_first, _middle, _last, _year, _month, _day,
			_phn, _hour, _minute, _symptoms) {
		
		category = _category;
	}
	erPatient(const erPatient& other):patient(other) {
		category = other.category;
	}
	~erPatient() {}
	string get_category() const {
		return category;
	}
	virtual void print() const {
		patient::print();
		cout << "   <category>: " << category << endl;
	};
};