#ifndef PACKAGE
#define PACKAGE

#include "FlightTicket.H"
#include "HotelVoucher.H"
#include "EventTicket.H"
#include "Constants.h"

class Package {
private:
     FlightTicket flights[2] = {};
     HotelVoucher* hotels;
     EventTicket* events;
     double totalCost;
     double totalProfit;
     int nightsStaying;
     int eventCount;
     bool feasible;
public:
    Package();
	Package(FlightTicket* flights, HotelVoucher* hotels, EventTicket* events, int eventCount);
	~Package();
	clean();
	void printAll();
	double getTotalCost() const;
	double getTotalProfit() const;
    void getStats(int*& flyinCount, int*& flyoutCount,
                  int*& eventCount,
                  int**& hotelVoucherCount);
    bool isfeasible() const;
};

#endif
