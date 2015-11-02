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

This header declares a class Event with 2 derived classes : TickEvent (to hold incoming tick data from OANDA) and OrderEvent (to hold the orders sent to OANDA based upon strategy and signal). The reason for deriving them from same class is that we want to store them in same queue of type base Event class pointer

Event.cpp

Defines the TickEvent and OrderEvent classes derived from Event class. The bid and ask prices are stored in TickEvent class.
OrderEvent class stores order type and other details of the order.

StreamingForexPrices.h

class StreamingForexPrices is derived from base class thread from thread.h
This would enable it to run as a separate thread. The class uses C library CURL to connect to OANDA API. 
void StreamingForexPrices::stream_to_queue(void) function sets various options using CURL to get quotes from the API. A callback called WriteMemoryCallback is used (a callback is a piece of executable code that is passed as an argument to other code, which is expected to call back (execute) the argument at some convenient time) to store the data receivd from API into a structure.
static size_t StreamingForexPrices::WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) function parses the data *contents

Execution.h

Declaration for Class Execution

Execution.cpp

To take the Event pointer as argument, cast to OrderEvent and get the instrument, order type, units to buy/sell. 
Then post this order using through OANDA API using libcurl.






