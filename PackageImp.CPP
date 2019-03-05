#include "Package.H"
#include "Constants.h"
#include <iostream>
#include <cmath>

//Constructors
Package::Package(){
    feasible = false;
}

Package::Package(FlightTicket* flights, HotelVoucher* hotels, EventTicket* events, int eventCount){
    //Get nights staying
    nightsStaying = flights[1].getDate()-flights[0].getDate();
    this->eventCount = eventCount;

    totalCost = 0;
    totalProfit = 0;

    for(int i=0; i<2; i++){
        this->flights[i] = flights[i];
        totalCost += flights[i].getTicketPrice();
        totalProfit += flights[i].getTicketPrice()*0.05;
    }

    this->hotels = new HotelVoucher[nightsStaying];
    for(int i=0; i<nightsStaying; i++){
        this->hotels[i] = hotels[i];
        totalCost += hotels[i].getTicketPrice();
        totalProfit += hotels[i].getTicketPrice()*0.05;
    }

    this->events = new EventTicket[eventCount];
    for(int i=0; i<eventCount; i++){
        this->events[i] = events[i];
        totalCost += events[i].getTicketPrice();
        totalProfit += events[i].getTicketPrice()*0.1;
    }

    feasible = true;
}

//Deconstrutor
Package::~Package(){}

Package::clean(){
    if(feasible){
        delete[] hotels;
        delete[] events;
    }
}

//Getters
double Package::getTotalCost() const{ return totalCost; }
double Package::getTotalProfit() const{ return totalProfit; }
bool Package::isfeasible() const{ return feasible; }

//Public Functions
void Package::printAll(){
    //Header
    cout << "The package contains : " << endl;

    //Contents
    for(int i=0; i<2; i++)            flights[i].printTicket();
    for(int i=0; i<nightsStaying; i++) hotels[i].printTicket();
    for(int i=0; i<eventCount; i++)    events[i].printTicket();

    //Values
    cout << "Total cost of the package is $" << totalCost << endl
         << "Total profit of the package is $" << totalProfit << endl;

    //Validity
    cout << "The package is valid.";
}

void Package::getStats(int*& flyinCount, int*& flyoutCount,
                  int*& eventsCount,
                  int**& hotelVoucherCount){
    //Get flight stats
    flyinCount[ flights[0].getDate()] += 1;
    flyoutCount[flights[1].getDate()] += 1;

    //Get hotel stats
    for(int i=0; i<nightsStaying; i++)
        hotelVoucherCount[hotels[i].getValue()][hotels[i].getDate()] += 1;

    //Get event stats
    for(int i=0; i<eventCount; i++)
        eventsCount[events[i].getValue()];
}
