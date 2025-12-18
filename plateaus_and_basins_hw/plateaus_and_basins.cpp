#include <iostream>
#include "functions.h"

using std::cout, std::cin, std::endl;

int main() {
	bool quit = false;
	// Note: we use long long because the input number can exced the system max limit 
	// for what an int can hold 
	long long a = 1000;
	long long b = 5000;
	while (!quit) {
		cout << "Enter number: ";
		cin >> a >> b;
		if(a == 0) {
			quit = true;
			break;
		}
		while(!is_valid_range(a, b)) {
			cout << "Invalid Input" << endl;
			cout << "number >=1000 &&  number <1000000000000: ";
			cin >> a >> b;
		}
		count_valid_pb_numbers(a, b);
	}
	return 0;
}

