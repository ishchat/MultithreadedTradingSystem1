#include "Event.h"

Event::Event()
{
    type="BASE";
}

TickEvent::TickEvent(std::string _instrument,std::string _time,double _bid,double _ask)
{
    type="TICK";
	instrument=_instrument;
	time=_time;
	bid=_bid;
	ask=_ask;
}

OrderEvent::OrderEvent(std::string _instrument,int _units,std::string _order_type,std::string _side)
{
    type="ORDER";
	instrument=_instrument;
	units=_units;
	order_type=_order_type;
	side=_side;
}
