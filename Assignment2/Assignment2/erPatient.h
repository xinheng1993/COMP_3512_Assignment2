#pragma once
#include "Patient.h"

class erPatient:public patient {
protected:
	string category;
	int admin_hour, admin_minute;
	Date adminDate = Date::today();
public:
	erPatient() {};
	erPatient(string _first, string _middle, string _last,int _year, int _month, int _day, int _phn, 
		int _hour, int _minute,string _symptoms,string _category):patient(_first, _middle, _last, _year,
			_month, _day,_phn, _symptoms) {
		admin_hour = _hour;
		admin_minute = _minute;
		category = _category;
	};
	erPatient(const erPatient& other):patient(other) {
		category = other.category;
		admin_hour = other.admin_hour;
		admin_minute = other.admin_minute;
		adminDate = other.adminDate;
	};
	~erPatient() {};
	int get_hour() const {return admin_hour;}
	int get_minute() const {return admin_minute;}
	string get_category() const {return category;}
	Date& get_adminDate() {return adminDate;}
	void set_cate(int cate_idx){ 
		Category c;
		category = c.categorys[cate_idx];
	};
	void set_adminDate(int& year, int& mon, int& day) {
		adminDate.set_date(year, mon, day);
	}

	virtual void print() const {
		patient::print();
		cout << "   <admin_date>: " << adminDate <<"\n"
			 << "   <admission time>: " << setw(2) << setfill('0') << admin_hour
			 << ":" << setw(2) << setfill('0') << admin_minute <<"\n"
			 << "   <category>: " << category << endl;
	}
};