#ifndef TICKET_E_
#define TICKET_E_

#include "Ticket.H"
#include <string>
using namespace std;

class EventTicket: public Ticket {
private:
    int eID;
public:
    EventTicket();
	EventTicket(int id);
	~EventTicket(){}
	void printTicket();
	int getValue() const;
};

#endif
