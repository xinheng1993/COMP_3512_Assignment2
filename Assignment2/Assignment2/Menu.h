#pragma once
#include <iostream>
#include "Category.h"
#include "Patient.h"
#include <thread>
#include <chrono>
#include <iomanip>
#include <string>
using namespace std;
class menu {
public:
	virtual void retry_home(bool is_error) = 0;
	virtual void home_page() = 0;
	virtual string category_page() = 0;
};