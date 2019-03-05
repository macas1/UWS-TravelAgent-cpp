#include "HotelVoucher.H"
#include "Constants.h"
#include <iostream>
using namespace std;

//Constructors
HotelVoucher::HotelVoucher(){}
HotelVoucher::HotelVoucher(int d, int s, double v):Ticket(d, hotelPriceMap[s-LOWESTSTARS]), stars(s){
    discount = 0.0;
    switch(s){
        case 4: if(v > 0.5) discount = 0.2;
                break;
        case 5: if(v > 0.2) discount = 0.2;
                if(v > 0.5) discount = 0.4;
                break;
        default: break;
    }
}

//Public Functions
void HotelVoucher::printTicket(){
    cout << "Hotel voucher for a " << stars
         << " star room on day " << date
         << " at price $" << getTicketPrice() << endl;
}

//Getters
int HotelVoucher::getValue() const{ return stars; }
