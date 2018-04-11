#include"Menu.h"
#include "ER.h"
#include "Date.h"
#include<string>
using namespace std;

int main() {
	
	Er erSystem;
	
	erSystem.system_start();
	
	//vector<int> vec;
	//vec.push_back(5);
	//vec.push_back(7);
	//vec.push_back(9);
	//vec.erase(vec.begin());
	//for (unsigned i = 0; i<vec.size(); ++i)
	//	std::cout << ' ' << vec[i];
	//std::cout << '\n';
	//time_t now = time(0);

	//cout << "Number of sec since January 1,1970:" << now << endl;

	//tm *ltm = localtime(&now);

	//// print various components of tm structure.
	//cout << "Year" << 1970 + ltm->tm_year << endl;
	//cout << "Month: " << 1 + ltm->tm_mon << endl;
	//cout << "Day: " << ltm->tm_mday << endl;
	//cout << "Time: " << ltm->tm_hour << ":";
	//cout << ltm->tm_min << ":";
	//cout << ltm->tm_sec << endl;

	system("pause");
	return 0;
}