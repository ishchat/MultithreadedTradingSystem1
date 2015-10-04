#ifndef EVENT_H
#define EVENT_H

#include <string>

class Event
{
public:
	std::string type;
	Event();
};

class TickEvent : public Event
{
public:
	TickEvent(std::string _instrument,std::string _time,double _bid,double _ask);
	//std::string type;
	std::string instrument;
	std::string  time;
	double bid;
	double ask;
};

class OrderEvent : public Event
{
public:
	OrderEvent(std::string _instrument,int _units,std::string _order_type,std::string _side);
	//std::string type;
	std::string instrument;
	int units;
	std::string order_type;
	std::string side;
};

#endif // EVENT_H
