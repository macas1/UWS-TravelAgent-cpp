#ifndef TICKET_H_
#define TICKET_H_

#include "Ticket.H"

class HotelVoucher: public Ticket {
private:
    int stars;
public:
    HotelVoucher();
	HotelVoucher(int d, int s, double v);
	~HotelVoucher(){};
	void printTicket();
	int getValue() const;
};

#endif
