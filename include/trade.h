#ifndef TRADE_H
#define TRADE_H

#include <iostream>
#include "thread.h"
#include "wqueue.h"
#include "Event.h"
#include "strategy.h"
#include "Execution.h"

extern wqueue<Event*> events_queue;

class trade: public Thread
{
    public:
    Event* event;

	std::string a_domain, access_token, account_id, instruments;
	int units;

        trade(string , string, string, string, int);
        void* run();
};

#endif // TRADE_H
