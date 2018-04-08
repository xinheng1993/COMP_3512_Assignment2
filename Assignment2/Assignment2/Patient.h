#pragma once
#include <string>
using namespace std;


class patient {
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
	patient(string f, string mi, string l, int y, int m, int d,int p, int h, int minute, string sym) {
		first = f;
		middle = mi;
		last = l;
		year = y;
		month = m;
		days = d;
		phn = p;		
		hour = h;
		minute = minute;
		symptoms = sym;
	}
	patient(patient& other) {
		first = other.first;
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

};
