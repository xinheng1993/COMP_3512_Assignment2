#pragma once
#include <chrono>
#include "Category.h"
#include <iomanip>
#include <iostream>
#include "Patient.h"
#include <string>
#include <thread>

using namespace std;

class menu {
public:
	virtual void retry_home(bool is_error) = 0;
	virtual void home_page() = 0;
	virtual string category_page() = 0;
};