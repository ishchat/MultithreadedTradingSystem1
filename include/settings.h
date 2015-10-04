#ifndef SETTINGS_H
#define SETTINGS_H

#include <iostream>
#include <map>
#include <string>

using namespace std;

class settings
{
public:
//We are using static variables here as we are not going to define objects for this class
//This class is only used to wrap variables as we don't want too many global variables since we use many source files
//in a project
//Constructor can't be used to initialize static variables so we initialize them as shown in source file

static map <std::string, std::string> streaming;

static map<std::string, std::string> api;

static map<std::string, map<std::string, std::string> > ENVIRONMENTS;

static string A_DOMAIN;
static string STREAM_DOMAIN;
static string API_DOMAIN;
static string ACCESS_TOKEN;
static string ACCOUNT_ID;

};

#endif // SETTINGS_H
