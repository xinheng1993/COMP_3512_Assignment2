#pragma once
#include <string>
#include <iomanip>
#include "Date.h"

using namespace std;

class patient {
	string first, middle, last, symptoms;
	int phn;
	Date birthday;
	
public:
	//default constructor
	patient(){}

	//construcor with parameters
	patient(string _first, string _middle, string _last, 
		int _year, int _month, int _day,int _phn,string _symptoms) {
		first = _first;
		middle = _middle;
		last = _last;
		Date temp(_year, _month, _day);
		birthday = temp;
		phn = _phn;
		symptoms = _symptoms;
	}

	//copy constructor
	patient(const patient& other) {
		first = other.first;
		middle = other.middle;
		last = other.last;
		birthday = other.birthday;
		phn = other.phn;
		symptoms = other.symptoms;
	}

	//destructor
	~patient() {}

	//getters and setters
	string get_first() const {return first;}
	string get_middle() const {return middle;}
	string get_last() const {return last;}
	Date get_birthday() const {return birthday;}
	int get_phn() const {return phn;}
	string get_symptoms() const{return symptoms;}

	//print patient
	virtual void print() const {
		cout << setw(72) << setfill('*') << "" << endl;
		cout << "   <name>: " << first << " " << middle << " " << last << "\n"
			<< "   <health number>:" << setw(8) << setfill('0') << phn << endl;
	}
};
