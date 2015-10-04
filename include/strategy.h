#ifndef STRATEGY_H
#define STRATEGY_H

#include <string>
#include <random>
#include "thread.h"
#include "wqueue.h"
#include "Event.h"

/*
class strategy
{
    public:
    static std::string instrument;
    static int units;
    static int ticks;
    strategy(std::string, int);
    static void calculate_signals(Event*);
};*/
//
class strategy
{
    public:
    std::string instrument;
    int units;
    int ticks;
    strategy(std::string, int);
    void calculate_signals(Event*);
};

#endif // STRATEGY_H
