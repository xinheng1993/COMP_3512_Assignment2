#include"Menu.h"
#include "ER.h"
#include "Date.h"
#include<string>
using namespace std;

int main() {
	
	Er erSystem;
	
	erSystem.system_start();
	
	//try {
	//	Date d(-1, -1, -1);
	//}
	//catch (std::invalid_argument e) {
	//	std::cout << e.what() << std::endl;
	//}

	//Date today = Date::today();
	//std::cout << today << std::endl;
	//today.set_date(1990, 4, 10);
	//today = Date(1990, 4, 10);

	/*std::cout << today << std::endl;*/


	system("pause");
	return 0;
}