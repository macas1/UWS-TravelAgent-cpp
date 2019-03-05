#ifndef CONSTANTS_H_
#define CONSTANTS_H_
#include <string>
using namespace std;

//How long the chosen period is
const int NUMBEROFDAYS = 10;

//Event data
const string nameMap[] = { "Opening", "Soccer 1", "Soccer 2", "Soccer 3",
		"Track and Field 1", "Track and Field 2", "Track and Field 3",
		"Track and Field 4", "Swimming 1", "Swimming 2", "Gymnastics 1",
		"Gymnastics 2", "Basketball 1", "Basketball 2", "Closing" };

const int eventPriceMap[] = { 2000, 80, 160, 500, 80, 100, 120, 140, 100, 100, 60, 100, 150, 300, 800 };
const int eventDateMap[]  = {0,     3,  6,   9,   1,   2,  3,   4,   5,   6,   7,  8,   5,   7,   9};
const int eventQuota[]    = {60,    47, 30,  22,  50,  52, 42,  25,  37,  20,  43, 34,  35,  30,  40};
const int MAXEVENTS       = 10;
const int NUMBEROFEVENTS  = 15;

//Hotel data
const int hotelPriceMap[] = {160, 210, 320}; // room price per night
const int hotelQuota[]    = {20,  25,  30};  // rooms availible per day
const int LOWESTSTARS     = 3;
const int NUMBEROFHOTELS  = 3;

//Flight data
const int FLIGHTPRICE = 2000;

//Generator limits
const int MINREQUESTS  = 100;
const int MAXREQUESTS  = 150;


#endif /* CONSTANTS_H_ */
