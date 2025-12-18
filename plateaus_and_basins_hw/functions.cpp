#include <iostream>
#include "functions.h"

using std::cout, std::endl;

// this function checks if the range is valid
bool is_valid_range(long long a, long long b) {
	long long num1 = 1000;
	long long num2 = 1000000000000;
	if (a < num1 || b >= num2) {
        return false;
    }
    else if(a>b) {
        return false;
    }
	else {
        return true;
    }
}

// classify_geo_type operates on a number, slices it and detects if it is plateau, basin or none
// it is called recursively by count_valid_pb_numbers
char classify_geo_type(long long number) {
   int count = 0;
   long long workingnum = number;


   // Count number of digits
   while (workingnum > 0) {
       workingnum = workingnum / 10;
       ++count;
   }


   workingnum = number;
   int digit = 0, previous = 0;
   digit = workingnum % 10;  // Get the last digit
   workingnum /= 10;
   int count1 = count - 1;
   char returnchar = 'n';


   // Key loop to detect plateau
   bool switchslope = false;
   bool trigger = true;

	//cout<<"plat"<<number<<endl;
	//cout<<workingnum<<endl;
	//cout<<"count:"<<count1<<endl;
   while (trigger) {

       while (!switchslope) { 
		//cout << "Not switch" << endl;
		
		previous = digit;
		digit = workingnum % 10;
       	workingnum /= 10;
      	--count1;
		//cout<<workingnum<<endl;
		//cout<<"count:"<<count1<<endl;
			if((count1 == count - 2) && (previous == digit)) {
				trigger = false;
				break;
			}
		
           if (count1 == 0) {
               trigger = false;
               break;
           }
           if (previous == digit) {
               switchslope = true;
               break;
           } else if (digit > previous) {
               continue;
           } else {
               trigger = false;
               break;
           }
       }

       if (trigger == false) {
        break;
       }


       while (switchslope) { 
			//cout << "Switched" << endl;

			previous = digit;
			digit = workingnum % 10;
       		workingnum /= 10;
      		--count1;
			//cout<<workingnum<<endl;
			//cout<<"count:"<<count1<<endl;
           if (digit <= previous) {
               if (count1 == 0) {
				//cout << "at last" << "last dig=" << digit << "prev dig" << previous<< endl;

                   if (digit != previous && digit < previous) {
                       returnchar = 'p';  // Plateau detected
                       trigger = false;
                       break;
                   }
				   else {
						trigger = false;
						break;
				   }

                }
                   
               
               else {

                   continue;
               }
           }
           else {
               trigger = false;
               break;
           }
       }
   }


   	workingnum = number;
   	digit = 0;
	previous = 0;
	digit = workingnum % 10;  // Get the last digit
   	workingnum /= 10;
    count1 = count - 1;


   // Key loop to detect basin
   switchslope = false;
   trigger = true;

	//cout<<"bas"<<number<<endl;
	//cout<<workingnum<<endl;
	//cout<<"count:"<<count1<<endl;
   while (trigger) {

       while (!switchslope) { 
		//cout << "not switched" << endl;
		previous = digit;
		digit = workingnum % 10;
       	workingnum /= 10;
      	--count1;
		//cout<<workingnum<<endl;
		//cout<<"count:"<<count1<<endl;
			if((count1 == count - 2) && (previous == digit)) {
				trigger = false;
				break;
			}
           if (count1 == 0) {
               trigger = false;
               break;
           }
           if (previous == digit) {
               switchslope = true;
               break;
           } else if (digit < previous) {
               continue;
           } else {
               trigger = false;
               break;
           }
       }

       if (trigger == false) {
        break;
       }


       while (switchslope) { 
		//cout << "switched" << endl;
			previous = digit;
			digit = workingnum % 10;
       		workingnum /= 10;
      		--count1;
			//cout<<workingnum<<endl;
			//cout<<"count:"<<count1<<endl;
           if (digit >= previous) {
               if (count1 == 0) {
				//cout << "at last" << "last dig=" << digit << "prev dig" << previous<< endl;
                   if (digit != previous && digit > previous) {
                       returnchar = 'b';  // Plateau detected
                       trigger = false;
                       break;
                   }
				   else {
						trigger = false;
						break;
				   }

                }
                   
               
               else {

                   continue;
               }
           }
           else {
               trigger = false;
               break;
           }
       }
   }


   return returnchar;
}


void count_valid_pb_numbers(long long a, long long b) {
	long long int distance = b-a;
	int plat_count = 0;
	int bas_count = 0;
	char x;

	// TODO for loop to iterate from 0 to distance
	for(long long i = a; i<=b; i++) {
		x = classify_geo_type(i);
		//cout << i << endl;
		//cout << x << endl;
		if (x == 'p') {
			++plat_count;
		}
		else if (x == 'b') {
			++bas_count;
		}
		else {
			continue;
		}
	}
	// recursively call classify_geo_type
	// count plateaus and basins based on char returned

	cout << "There are ";
	cout << plat_count;
	cout << " plateaus and ";
	cout << bas_count;
	cout << " basins between ";
	cout << a;
	cout << " and ";
	cout << b;
	cout <<'.' << endl;
}