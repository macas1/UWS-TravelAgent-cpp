#include "ClientRequest.H"
#include <iostream>
#include <iomanip>
#include <regex>
#include <algorithm>
using namespace std;

//Constructors
ClientRequest::ClientRequest() {
    cId = -1;
    hotelType = -1;
    budget = -1;
    valid = false;
    for (int i=0; i<NUMBEROFEVENTS; i++)
        events[i] = false;
}

ClientRequest::ClientRequest(int id, int ht, int b, bool e[NUMBEROFEVENTS]):cId(id), hotelType(ht), budget(b){
    for (int i=0; i<NUMBEROFEVENTS; i++)
        events[i] = e[i];
     valid = true;
}

ClientRequest::ClientRequest(int id, string input){
    regex r("[0-9]+,["+to_string(LOWESTSTARS)+"-"+to_string(LOWESTSTARS+NUMBEROFHOTELS-1)+"]+\\[[0-9]*(,[0-9]*)*\\]");
    if(!regex_match(input,r)) return;

    //Split into events and other data
    int noOfChosenEvents;
    string* data      = split(input, ',', noOfChosenEvents, 2);
    string* eventsStr = split(data[1].substr(2, data[2].length()-2), ',', noOfChosenEvents, -1);

    //Set basic data
    budget    = stoi(data[0]);
    hotelType = data[1].at(0)-'0';

    //Set events
    valid = true;
    if(noOfChosenEvents==0) return;

    for (int i=0; i<NUMBEROFEVENTS; i++)
        events[i] = false;

    int eventNo;
    for (int i=0; i<noOfChosenEvents; i++){
        eventNo = stoi(eventsStr[i]);
        if(eventNo < 0 || eventNo >= NUMBEROFEVENTS)  valid = false;
        else events[eventNo] = true;
    }

    cId = id;


}

//Getters
int ClientRequest::getId() const{ return cId; }
int ClientRequest::getHotelType() const{ return hotelType; }
int ClientRequest::getBudget() const{ return budget; }
bool* ClientRequest::getEvents(){ return events; }
bool ClientRequest::getValid() const{ return valid; }

//Private functions
string* ClientRequest::split(string s, char delimteter, int& length, int max){
    length = std::count(s.begin(), s.end(), delimteter) +1;
    if(max > 0 && length > max) length = max;
    string* output = new string[length];

    int counter  = 0;
    for(int i=0; i<s.length(); i++){
        if(s[i]==delimteter && !(max > 0 && counter>=max-1)){
            counter++;
        }else{
            output[counter] += s[i];
        }
    }

    return output;
}

//Public Functions
int ClientRequest::earliestEventDate() {
    int date = NUMBEROFDAYS;
    for (int i=0; i<NUMBEROFEVENTS; i++)
        if(events[i] && eventDateMap[i] < date)
            date = eventDateMap[i];

    if(date == NUMBEROFDAYS) return -1;
    return date;
}

int ClientRequest::latestEventDate() {
    int date = -1;
    for (int i=0; i<NUMBEROFEVENTS; i++)
        if(events[i] && eventDateMap[i] > date)
            date = eventDateMap[i];

    return date;
}

void ClientRequest::print() {
    cout << "Client " << cId << ":\t" << budget << "\t" << hotelType << "\t";

    for (int i = 0; i < NUMBEROFEVENTS; i++)
        if(events[i]) cout << i << "  ";
    cout << endl;
}

void  ClientRequest::reject(){ valid = false;}
