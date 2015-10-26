# MultithreadedTradingSystem1

thread.h

C++ thread related functions have been put in JAVA-style thread class. This class has been taken from vichargrave blog. It has runthread() function which calls virtual run() function defined in base thread class. Virtual functions :http://www.programiz.com/cpp-programming/virtual-functions
So the class derived from this class can have defintion of run.

thread.cpp 

Different C pthread library function wrappers for JAVA - style thread class taken from vichargrave blog.

settings.h

This header file contains settings class which has declarations for various OANDA API - related variables to be used in the project. Examples of these variables include API_DOMAIN, ACCESS_TOKEN etc

settings.cpp

This file contains the values of the declared variables in settings.h





