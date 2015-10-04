#include "Execution.h"

Execution::Execution(string _a_domain, string _access_token, string _account_id)
{
	a_domain = _a_domain;
	access_token = _access_token;
	account_id = _account_id;
}

static void Execution::execute_order(Event* event)
{

char *domain = a_domain.c_str();
char *accessToken = access_token.c_str();
char *accounts = account_id.c_str();

char * instrument = (((OrderEvent*) event)->instrument).c_str();
int units = ((OrderEvent*) event)->units;
char * order_type = (((OrderEvent*) event)->order_type).c_str();
char * side = (((OrderEvent*) event)->side).c_str();

	//remove the following 3 variables later:
//char *domain = "https://api-fxpractice.oanda.com";
//char *accessToken = "5e9aaced29ab4abaffa0351ea158a7fe-7a8af5fefcba44a1ea21cc3a18780045";
//char *accounts = "5267243";

 CURL *curl_handle;
  CURLcode res;

  char authHeader[100];
  char url[100];
  char orderstr[100];

if (snprintf(authHeader, 100, "Authorization: Bearer %s", accessToken) >= 100)
        exit(1);
        /*https://api-fxtrade.oanda.com/v1/accounts/12345/orders*/
//if (snprintf(url, 100, "%s/v1/prices?accountIds=%s&instruments=EUR_USD", domain, accounts) >= 100)
if (snprintf(url, 100, "%s/v1/accounts/%s/orders", domain, accounts) >= 100)
        exit(1);
if (snprintf(orderstr, 100, "instrument=%s&units=%d&side=%s&type=%s",instrument, units, side, order_type) >= 100)
        exit(1);

  struct curl_slist *hdr = NULL;

  //struct MemoryStruct chunk;

  //chunk.memory = malloc(1);  /* will be grown as needed by the realloc above */
  //chunk.size = 0;    /* no data at this point */

  curl_global_init(CURL_GLOBAL_ALL);

  /* init the curl session */
  curl_handle = curl_easy_init();

  /* specify URL to get */
  //curl_easy_setopt(curl_handle, CURLOPT_URL, "http://api-sandbox.oanda.com/v1/prices?instruments=EUR_USD%2CUSD_CAD%2CUSD_JPY");

   curl_easy_setopt(curl_handle, CURLOPT_URL, url);

  /* send all data to this function  */
  //curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

  /*https://fxtrade.oanda.com/community/forex-forum/topic/54006025/?page=1#post-9925345 */
  /*https://www.quantstart.com/articles/Forex-Trading-Diary-1-Automated-Forex-Trading-with-the-OANDA-API */
  /*http://developer.oanda.com/rest-live/development-guide/ */

        // uncomment to add authorization header: not required for sandbox
        hdr = curl_slist_append(hdr, "Content-Type: application/x-www-form-urlencoded");
        hdr = curl_slist_append(hdr, authHeader);

        /* use custom headers */
        res=curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, hdr);

        curl_easy_setopt(curl_handle, CURLOPT_CUSTOMREQUEST, "POST");
        curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, "instrument=EUR_USD&units=1000&side=buy&type=market");

        //curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, "stopLoss=1.0");

  /* we pass our 'chunk' struct to the callback function */
  //curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);

  /* some servers don't like requests that are made without a user-agent
     field, so we provide one */
  //curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

  /* get it! */
  std::cout<<"before curl_easy_perform";
  res = curl_easy_perform(curl_handle);
  std::cout<<"after curl_easy_perform";

  //free(chunk.memory);

  /* we're done with libcurl, so clean it up */
  curl_global_cleanup();

return;
}
