#ifndef TICKET_F_
#define TICKET_F_

#include "Ticket.H"

class FlightTicket: public Ticket {
private:
    bool flightIn;
public:
    FlightTicket();
	FlightTicket(int d, int f, bool fi);
	~FlightTicket(){}
	void printTicket();
};

#endif
