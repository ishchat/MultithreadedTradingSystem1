#ifndef STREAMINGFOREXPRICES_H
#define STREAMINGFOREXPRICES_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <memory>
#include <curl/curl.h>
#include <json-c/json.h>
#include "thread.h"
#include "wqueue.h"
#include "Event.h"
#include "settings.h"

using namespace std;

extern wqueue<Event*> events_queue;

//extern wqueue<std::unique_ptr<Event>> events_queue;

class StreamingForexPrices: public Thread
{
public:
	string a_domain, access_token, account_id, instruments;

	StreamingForexPrices(string , string, string, string);

struct MemoryStruct {
  char *memory;
  size_t size;
};

void stream_to_queue(void);

static size_t WriteMemoryCallback(void *, size_t, size_t, void *);

void* run();

};

#endif // STREAMINGFOREXPRICES_H
