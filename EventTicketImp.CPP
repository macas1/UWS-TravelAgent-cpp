#include "EventTicket.H"
#include "Constants.h"
#include <iostream>
#include <string>
using namespace std;

//Constructors
EventTicket::EventTicket(){}
EventTicket::EventTicket(int id):Ticket(eventDateMap[id], eventPriceMap[id]), eID(id){
    discount = 0.0;
}

//Public Funcitons
void EventTicket::printTicket(){
    cout << "Event Ticket for -" << nameMap[eID]
         << "- on day " << date
         << " at price $" << getTicketPrice() << endl;
}

//Getters
int EventTicket::getValue() const{ return eID; }
