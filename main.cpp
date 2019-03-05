#include "TravelAgent.H"
#include "FlightTicket.H"
#include "EventTicket.H"
#include "HotelVoucher.H"
#include "Package.H"
#include <iostream>

int main(){
    cout << "Choose a class to test:\n"
         << "1. Test basic classes\n"
         << "2. Test request generator class\n"
         << "3. Test simple travel agent\n"
         << "4. Test sorted travel agent\n"
         << "5. Test smart travel agent\n"
         << "6. Quit\n";

    string choice;
    cin >> choice;
    if(choice=="1"){
        //ClientRequest todo fix for invalid
        cout << "Test ClientRequest Class ...\n"
              << "Client No\tbudget\thotel\tevents"
              << endl;
        ClientRequest cr = ClientRequest(1, "9020,4,[14]");
        cr.print();
        cout << "Earliest event date: " << cr.earliestEventDate() << endl
             << "Latest event date: " << cr.latestEventDate() << endl;

        //FlightTickets
        cout << "\nTest FlightTicket Class ...\n";
        FlightTicket fi = FlightTicket(3, FLIGHTPRICE, true);
        fi.printTicket();
        FlightTicket fo = FlightTicket(8, FLIGHTPRICE, false);
        fo.printTicket();

        //EventTickets
        cout << "\nTest EventTicket Class ...\n";
        EventTicket e1 = EventTicket(2);
        e1.printTicket();
        EventTicket e2 = EventTicket(5);
        e2.printTicket();
        EventTicket e3 = EventTicket(14);
        e3.printTicket();

        //HotelVouchers
        cout << "\nTest HotelVoucher Class ...\n"
             << "set 3 star room on day 4 without discount" << endl;
        HotelVoucher h = HotelVoucher(4, 3, 0.0);
        h.printTicket();
        cout << "set 4 star room on day 9 with 0.2 discount" << endl;
        h = HotelVoucher(9, 4, 1.0);
        h.printTicket();

        cout << "set 5 star room on day 0 with 0.4 discount" << endl;
        h = HotelVoucher(0, 5, 1.0);
        h.printTicket();

        //Packages
        cout << "\nTest Package class:\nExample package 1 ...\n";
        FlightTicket fs[2] = {fi, fo};
        HotelVoucher hs[5] = {HotelVoucher(3, 4, 1.0),
                              HotelVoucher(4, 4, 1.0),
                              HotelVoucher(5, 4, 1.0),
                              HotelVoucher(6, 4, 1.0),
                              HotelVoucher(7, 4, 1.0)
        };

        EventTicket  es[2] = {e1, e2};
        Package p = Package(fs, hs, es, 2);
        p.printAll();
    }
    else if(choice=="2"){
        cout << "Test RequestGenerator Class ...\n";
        TravelAgent ta = TravelAgent(true, -1);;
        ta.printClients();
        cout << "Client request bundle generated. Check the file!";
    }

    bool gen = false;
    if(choice=="3" || choice=="4" || choice=="5"){
        cout << "\nWould you like to generate new requests (y/n)?\n";
        string choice2;
        cin >> choice2;
        if(choice2 == "y" || choice2 == "Y" || choice2 == "yes" || choice2 == "YES") gen=true;
    }

    if(choice=="3"){
        TravelAgent ta = TravelAgent(false, 0);
        ta.printAll();
    }
    else if(choice=="4"){
        TravelAgent ta = TravelAgent(true, 1);
        ta.printAll();
    }
    else if(choice=="5"){
        TravelAgent ta = TravelAgent(true, 2);
        ta.printAll();
    }
    return 0;
}
