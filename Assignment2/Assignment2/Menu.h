#pragma once
#include <iostream>
#include "Category.h"
using namespace std;
class menu {
	category s;
public:
	menu() {}
	void retry(const char& page);
	void home_page();
	void category_page(string& category);

};