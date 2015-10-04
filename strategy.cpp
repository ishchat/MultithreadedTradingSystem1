#include "strategy.h"

extern wqueue<Event*> events_queue;

strategy::strategy(string _instrument, int _units)
{
        instrument = _instrument;
        units = _units;
        ticks = 0;
}

/*
static std::string strategy::instrument="EUR_USD";
static int strategy::units=5;
static int strategy::ticks=0;
*/

static void strategy::calculate_signals(Event* event)
{
	std::string side;
	if (event->type == "TICK")
	{
		ticks = ticks+1;
		if (ticks % 2 == 0)
		{
	     std::random_device rd;
         std::mt19937 gen(rd());
         std::uniform_int_distribution<> dis(1, 2);
		 if (dis(gen)==1) side="buy";else side="sell";
		 OrderEvent* order = new OrderEvent(instrument, units, "market", side);
	     events_queue.add(order);
		}
	}
}
