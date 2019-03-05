#include "Ticket.H"
using namespace std;

//Constructors
Ticket::Ticket(int d, int f):date(d), fullPrice(f) { discount = 0.0; }

//Deconstructors
Ticket::~Ticket() {}

//Getters
int Ticket::getDate() { return date; }
double Ticket::getTicketPrice() { return (1.0-discount) * fullPrice; }
int Ticket::getValue() const { return -1; }
