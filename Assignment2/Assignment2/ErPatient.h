#pragma once
#include "Patient.h"
class Er_patient : public patient {
	string category;
public:
	Er_patient(){}
	Er_patient(string f, string mi, string l, int y, int m, int d, int p, int h, int minute,string sym, string ca){
		patient(f, mi, l, y, m, d, p, h, minute, sym);
		category = ca;
	}
	Er_patient(Er_patient& other) {
		patient(other);
		category = other.category;
	}
	friend ostream& operator<<(ostream &out, patient &p) {
		out << "name: " << p.first << " " << p.middle << " " << p.last
			<< " health number:" << setw(8) << setfill("0")<< p.phn << " category:" << p.category
			<< " admission time:" << setw(2) << setfill("0")<<p.hour 
			<< ":" << setw(2) << setfill("0")<< p.minute << endl;
		return out;
	};
};