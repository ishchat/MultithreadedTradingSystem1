#ifndef EXECUTION_H
#define EXECUTION_H

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <curl/curl.h>
#include "Event.h"

using namespace std;


//const char* str_Array[] = {"application/x-www-form-urlencoded", "application/json", "text/*", NULL};
// Above array was not getting declared within class due to curly braces probably. So tried to put it outside but that didn't work also.
//So, finally put it inside class with the following technique:
//http://objectmix.com/c/244506-declaring-const-char-strings-class.html
//http://stackoverflow.com/questions/6536805/initializing-a-static-const-array-of-const-strings-in-c

class Execution
{
public:
	//http://objectmix.com/c/244506-declaring-const-char-strings-class.html
	//http://stackoverflow.com/questions/6536805/initializing-a-static-const-array-of-const-strings-in-c

	string a_domain, access_token, account_id, instruments;

	Execution(string , string, string);
	void execute_order(Event*);
};


#endif // EXECUTION_H
