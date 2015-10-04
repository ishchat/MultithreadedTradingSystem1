#include <string.h>
#include <iostream>
#include <map>
#include <utility>
#include <unistd.h>
#include "settings.h"
#include "Event.h"
#include "wqueue.h"
#include "StreamingForexPrices.h"
#include "trade.h"

/* Low latency links:
http://programmers.stackexchange.com/questions/183723/low-latency-unix-linux
http://codedependents.com/2014/01/27/11-best-practices-for-low-latency-systems/

*/
using namespace std;

extern wqueue<Event*> events_queue;

//extern wqueue<std::unique_ptr<Event>> events_queue;

int main()
{
   /*
   cout << "settings::STREAM_DOMAIN =" << settings::STREAM_DOMAIN  << endl << endl;
   wqueue<Event> queue;

    Event item;

    for (int i = 0; i < 10; i++) {
        queue.add(item);
        usleep(1);
    }


    item = queue.remove();
    cout<<"item.type :"<<item.type<<endl;
    */

    //StreamingForexPrices* thread1 = new ConsumerThread(queue);

    //StreamingForexPrices::stream_to_queue();

  cout<<settings::STREAM_DOMAIN;

//char *domain = "http://stream-sandbox.oanda.com";
    StreamingForexPrices* thread1 = new StreamingForexPrices("http://stream-sandbox.oanda.com",settings::ACCESS_TOKEN,settings::ACCOUNT_ID,"EUR_USD");
//string _a_domain, string _access_token, string _account_id, string _instruments
   //StreamingForexPrices* thread1;

   //thread1->stream_to_queue();
   thread1->start();

   trade* thread2 = new trade("http://api-fxpractice.oanda.com",settings::ACCESS_TOKEN,settings::ACCOUNT_ID,"EUR_USD", 5);
   thread2->start();
   /*Following lines have to be added as after executing instruction thread1->start()(which starts a parallel thread to main()),
   the control in main() thread immediately executes the next instruction return 0 which ends the main() thread and thus its
   child thread thread1 also ends. So thread1 does not get time to run. So we add a while(1) which keeps running (same
   as while(1){}) */
    // Ctrl-C to end program
    sleep(1);
    printf("Enter Ctrl-C to end the program...\n");
    while (1);
    exit(0);
   cout<<"yes";

   return 0;
}
