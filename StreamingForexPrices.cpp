#include "StreamingForexPrices.h"


StreamingForexPrices::StreamingForexPrices(string _a_domain, string _access_token, string _account_id, string _instruments)
{

        a_domain = _a_domain;
        access_token = _access_token;
        account_id = _account_id;
        instruments = _instruments;

}


void StreamingForexPrices::stream_to_queue(void)
{

//remove the following 3 variables later:
//char *domain = "http://stream-sandbox.oanda.com";
char *domain = a_domain.c_str();
//char *domain = "http://stream-fxpractice.oanda.com";
//char *accessToken = "5e9aaced29ab4abaffa0351ea158a7fe-7a8af5fefcba44a1ea21cc3a18780045";
//char *accessToken = (settings::ACCESS_TOKEN).c_str();
char *accessToken = access_token.c_str();
//char *accounts = "5267243";
//char *accounts = (settings::ACCOUNT_ID).c_str();
char *accounts = account_id.c_str();

CURL *curl_handle;
  CURLcode res;

  char authHeader[100];
  char url[100];

if (snprintf(authHeader, 100, "Authorization: Bearer %s", accessToken) >= 100)
        exit(1);
        /*https://stream-fxtrade.oanda.com/v1/prices?accountId=12345&instruments=AUD_CAD%2CAUD_CHF*/
if (snprintf(url, 100, "%s/v1/prices?accountIds=%s&instruments=%s", domain, accounts, instruments.c_str()) >= 100)
        exit(1);

  struct curl_slist *hdr = NULL;

  struct MemoryStruct chunk;

  chunk.memory = malloc(1);  /* will be grown as needed by the realloc above */
  chunk.size = 0;    /* no data at this point */

  curl_global_init(CURL_GLOBAL_ALL);

  /* init the curl session */
  curl_handle = curl_easy_init();

  /* specify URL to get */
  //curl_easy_setopt(curl_handle, CURLOPT_URL, "http://api-sandbox.oanda.com/v1/prices?instruments=EUR_USD%2CUSD_CAD%2CUSD_JPY");

   curl_easy_setopt(curl_handle, CURLOPT_URL, url);

  /* send all data to this function  */
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

        // uncomment to add authorization header: not required for sandbox
        hdr = curl_slist_append(hdr, authHeader);

        /* use custom headers */
        res=curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, hdr);

  /* we pass our 'chunk' struct to the callback function */
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);

  /* some servers don't like requests that are made without a user-agent
     field, so we provide one */
  curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

  /* get it! */
  std::cout<<"before curl_easy_perform";
  res = curl_easy_perform(curl_handle);
  std::cout<<"after curl_easy_perform";

  free(chunk.memory);

  /* we're done with libcurl, so clean it up */
  curl_global_cleanup();

return;

}

static size_t StreamingForexPrices::WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{

char * string;

string = (char*)contents;

std::string strFromChar;
strFromChar.append(string);

   std::size_t pos = strFromChar.find("tick");
  if (pos!=std::string::npos)
  {
    std::size_t pos1 = strFromChar.find(":");
    std::size_t pos2 = strFromChar.find("}");
         std::cout<<"} at "<<pos2<<std::endl;
    strFromChar=strFromChar.substr(pos1+1,pos2-1);
     std::cout<<"string "<<strFromChar<<std::endl;

string = strFromChar.c_str();
json_object * jobj = json_tokener_parse(string);

std::string instrument, time;
double bid, ask;

enum json_type type;

json_object_object_foreach(jobj, key, val) {

printf("\nkey %s\n", key);

std::string mycppstr(key);
if (mycppstr=="instrument")
{
std::string mycppstr2(json_object_get_string(val));
instrument=mycppstr2;
} else
if (mycppstr=="time")
{
std::string mycppstr2(json_object_get_string(val));
time=mycppstr2;
} else
if (mycppstr=="bid")
{
//std::string mycppstr2(json_object_get_double(val));
bid=json_object_get_double(val);
} else
if (mycppstr=="ask")
{
//std::string mycppstr2(json_object_get_double(val));
ask=json_object_get_double(val);
}

/*Add to queue*/
TickEvent* Tick = new TickEvent(instrument,time,bid,ask);
events_queue.add(Tick);

//TickEvent* item = (TickEvent*)events_queue.remove();
//cout<<"item->type"<<item->type<<item->instrument<<item->time<<item->bid<<item->ask;

// https://akrzemi1.wordpress.com/2013/12/11/type-erasure-part-iii/
// http://www.quora.com/How-can-I-implement-heterogeneous-arrays-in-C++
// https://isocpp.org/wiki/faq/containers

//TickEvent* Tick = new TickEvent(instrument,1.0,1.0,1.0);

//events_queue.add(std::unique_ptr<Event>{Tick});


printf("type: \n",type);

type = json_object_get_type(val);

switch (type) {

case json_type_null: printf("json_type_nulln");

break;

case json_type_boolean: printf("json_type_boolean");
//printf("value: %sn", json_object_get_boolean(val));
break;

case json_type_double: printf("json_type_double");
printf("\nvalue: %lf\n", json_object_get_double(val));
break;

case json_type_int: printf("json_type_int");
printf("\nvalue: %d\n", json_object_get_int(val));
break;

case json_type_object: printf("json_type_objectn");
break;

case json_type_array: printf("json_type_arrayn");
break;

case json_type_string: printf("json_type_string");
{
printf("\nvalue: %s\n", json_object_get_string(val));
}
break;

}
}
    }

  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;

  mem->memory = realloc(mem->memory, mem->size + realsize + 1);
  if(mem->memory == NULL) {
    /* out of memory! */
    printf("not enough memory (realloc returned NULL)\n");

    return 0;
  }

  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}


void* StreamingForexPrices::run() {
cout<<"run begins";
StreamingForexPrices::stream_to_queue();
cout<<"run ends";
return NULL;
}


