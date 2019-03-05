#include "ClientRequest.H"
#include "Package.H"
#include <array>

class TravelAgent {
private:
    double profit=0.0;
    ClientRequest* requests;
    Package* packages;
    int requestCount;
    int eventsBooked[NUMBEROFEVENTS] = {};
    int hotelsBooked[NUMBEROFDAYS][NUMBEROFHOTELS] = {};
    int flyinsBooked[NUMBEROFDAYS] = {};
    int flyoutBooked[NUMBEROFDAYS] = {};

    int getTotalProfit();
    void getRequests(bool genNew);
    void sortRequests();
    void createAllPackagesSmart();
    Package createPackageSmart(int index, int fi, int fo, int eventNum, int hotelNum, int tempHotelsBooked[NUMBEROFDAYS][NUMBEROFHOTELS], int tempEventsBooked[NUMBEROFEVENTS]);
    void createPackageFirst(int index);
public:
    static int getBit(int number, int bit, int base);
    TravelAgent(bool genNew, int type);
    void printClients();
    void printAll();
};

//When creating a package from a request, at lease one of the desired events must be added.
//He said we need to write requests out to a file? Is the generator meant to write to a file??
