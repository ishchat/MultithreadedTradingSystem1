#include "trade.h"

trade::trade(string _a_domain, string _access_token, string _account_id, string _instruments, int _units)
{
        a_domain = _a_domain;
        access_token = _access_token;
        account_id = _account_id;
        instruments = _instruments;
        units = _units;
}

void* trade::run() {
std::cout<<"run begins";

strategy* strategy_ptr = new strategy(instruments,units);
Execution* Execution_ptr = new Execution(a_domain, access_token, account_id);

    while(1)
    {
        //cout<<"removing"<<endl;
        event = events_queue.remove();
        //cout<<"removed"<<endl;
        if (event->type == "TICK")
        {
        if ((((TickEvent*) event)->ask) > 0)
        {
        cout<<"Event type is" << event->type<<endl;
        cout<<"Event instrument is" << ((TickEvent*) event)->instrument<<endl;
        cout<<"Event bid is" << ((TickEvent*) event)->bid<<endl;
        cout<<"Event ask is" << ((TickEvent*) event)->ask<<endl;
        strategy_ptr->calculate_signals(event);
        }
        }
         else if (event->type == "ORDER")
         {
          cout<<"Event type is" << event->type<<endl;
          cout<<"Event instrument is" << ((OrderEvent*) event)->instrument<<endl;
          cout<<"Event units is" << ((OrderEvent*) event)->units<<endl;
          cout<<"Event order_type is" << ((OrderEvent*) event)->order_type<<endl;
          cout<<"Event side is" << ((OrderEvent*) event)->side<<endl;
          cout<<"Executing order!";
          Execution_ptr->execute_order(event);

         }
      }
      std::cout<<"run ends";
return NULL;
}
