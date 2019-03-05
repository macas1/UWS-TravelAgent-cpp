#include "FlightTicket.H"
#include "Constants.h"
#include <iostream>

//Constructors
FlightTicket::FlightTicket(){}
FlightTicket::FlightTicket(int d, int f, bool fi):Ticket(d, f), flightIn(fi){
    if(!flightIn) d = (NUMBEROFDAYS-1)-d;
    discount = d*0.05;
}

//Public Functions
void FlightTicket::printTicket(){
    cout << "Flight ticket from ";
    if(flightIn) cout << "Sydney to Tokyo";
    else         cout << "Tokyo to Sydney";
    cout << " on day " << date
         << " at price $" << getTicketPrice() << endl;
}
