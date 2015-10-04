#include "settings.h"


map<string, string> settings::streaming =
{{"real","stream-fxtrade.oanda.com"},{"practice","stream-fxpractice.oanda.com"},{"sandbox","stream-sandbox.oanda.com"}};

map<string, string> settings::api =
{{"real","api-fxtrade.oanda.com"},{"practice","api-fxpractice.oanda.com"},{"sandbox","api-sandbox.oanda.com"}};

map<string, map<std::string, std::string>> settings::ENVIRONMENTS =
{{"streaming",streaming},{"api",api}};

string settings::A_DOMAIN = "practice";
string settings::ACCESS_TOKEN = "5e9aaced29ab4abaffa0351ea158a7fe-7a8af5fefcba44a1ea21cc3a18780045";
string settings::ACCOUNT_ID = "5267243";
string settings::STREAM_DOMAIN = settings::ENVIRONMENTS["streaming"][settings::A_DOMAIN];
