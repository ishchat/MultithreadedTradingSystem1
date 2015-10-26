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

wqueue.h

This header file declares the worker queue that forms the core data struccture for storing the incoming ticks.
The class is taken from the blog :  http://vichargrave.com/multithreaded-work-queue-in-c/ 
It has an add() function which applies a mutex lock to push back an item to a list structure.
There is a remove() function to pop from the front of the queue using a mutex lock.
(Mutex : A Mutex is a mutually exclusive flag. It acts as a gate keeper to a section of code allowing one thread in and blocking access to all others. This ensures that the code being controled will only be hit by a single thread at a time. Just be sure to release the mutex when you are done)

wqueue.cpp

Declares a  wqueue of type pointer to Event class : wqueue<Event*> events_queue;

Event.h

This header declares a class Event with 2 derived classes : TickEvent and OrderEvent




