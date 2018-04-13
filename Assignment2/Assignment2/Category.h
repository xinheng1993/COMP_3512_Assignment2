#pragma once
#include <string>
using namespace std;
class Category {
public:
	string categorys[6] = {
		"Critical and life - threatening, requires immediate care",
		"Critical, requires care very soon", 
		"Serious, requires care soon", //promoted in 1 hour
		"Serious", // promoted in 2hrs
		"Non - serious", // promoted in 3hrs
		"Not a priority" // promoted in 4 hrs
	};
};