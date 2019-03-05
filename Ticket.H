/*
 * Ticket.h
 *
 *  Created on: 27 Sep. 2018
 *      Author: dongmo
 */

#ifndef TICKET_
#define TICKET_

class Ticket {
protected:
	int date;
	int fullPrice;
	double discount;
public:
    Ticket(){}
	Ticket(int d, int f);
	int getDate();
	double getTicketPrice();
	~Ticket();

	virtual void printTicket(){};
	virtual int getValue() const;
};

#endif /* TICKET_ */
