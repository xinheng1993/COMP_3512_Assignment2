#pragma once
#include "Patient.h"

class erPatient:public patient {
protected:
	string category;
	int admin_hour, admin_minute, display_hour, display_min;
	Date adminDate = Date::today();
	Date updated_adminDate = Date::today();
public:
	erPatient() {};
	erPatient(string _first, string _middle, string _last,int _year, int _month, int _day, int _phn, 
		int _hour, int _minute,string _symptoms,string _category):patient(_first, _middle, _last, _year,
			_month, _day,_phn, _symptoms) {
		admin_hour = _hour;
		admin_minute = _minute;
		category = _category;
		display_hour = _hour;
		display_min = _minute;
	};
	erPatient(const erPatient& other):patient(other) {
		category = other.category;
		admin_hour = other.admin_hour;
		admin_minute = other.admin_minute;
		adminDate = other.adminDate;
		updated_adminDate = other.updated_adminDate;
		display_hour = other.display_hour;
		display_min = other.display_min;
	};
	~erPatient() {};

	int get_hour() const {return admin_hour;}
	void set_hour(int new_hour) { admin_hour = new_hour; }

	int get_minute() const {return admin_minute;}
	void set_minute(int new_min) { admin_minute = new_min; }

	int get_display_hour() const { return display_hour; }
	void set_display_hour(int dis_hour) { display_hour = dis_hour; }

	int get_display_minute() const { return display_min; }
	void set_display_minute(int dis_min) { display_min = dis_min; }

	void set_cate(string cate) { category = cate; }
	string get_category() const {return category;}
	
	Date& get_adminDate() {return adminDate;}
	void set_adminDate(int& year, int& mon, int& day) { adminDate.set_date(year, mon, day);}

	Date& get_updated_adminDate() { return updated_adminDate; }
	void set_updated_adminDate(int& year, int& mon, int& day) { updated_adminDate.set_date(year, mon, day); }

	virtual void print() const {
		patient::print();
		cout << "   <admin_date>: " << adminDate <<"\n"
			 << "   <admission time>: " << setw(2) << setfill('0') << display_hour
			 << ":" << setw(2) << setfill('0') << display_min <<"\n"
			 << "   <category>: " << category << endl;
	}
};