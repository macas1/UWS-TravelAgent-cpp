#include "TravelAgent.H"
#include "RequestGenerator.H"

#include "FlightTicket.H"
#include "HotelVoucher.H"
#include "EventTicket.H"

#include <fstream>
#include <list>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
//Constructors
TravelAgent::TravelAgent(bool genNew, int type){
    //Init
    getRequests(genNew);

    packages = new Package[requestCount];
    if(type==0 || type==1){
        if(type==1){sortRequests();}
        for(int i=0; i<requestCount; i++)
            createPackageFirst(i);
    }
    if(type==2){
        createAllPackagesSmart();
    }
}

//Private functions
void TravelAgent::sortRequests(){
    //Bubble sort
    bool swapped;
    ClientRequest temp;
    for (int i = 0; i < requestCount-1; i++){
        swapped = false;
        for (int j = 0; j < requestCount-i-1; j++){
            if (requests[j].getBudget() < requests[j+1].getBudget()) {
               temp = requests[j];
               requests[j] = requests[j+1];
               requests[j+1] = temp;
               swapped = true;
            }
        }
        if (swapped == false) break;
    }
}

void TravelAgent::createAllPackagesSmart(){
    //Declarations

    int count;
    int earliestEvent;
    int latestEvent;
    bool hotelsSame;
    int differentHotelTypes;
    int hotelPermutation;
    Package tempPackage;

    double best_singleProfit;
    int best_fi;
    int best_fo;

    int tempHotelsBooked[NUMBEROFDAYS][NUMBEROFHOTELS] = {};
    int tempEventsBooked[NUMBEROFEVENTS] = {};

    int tempHotelsBooked1[NUMBEROFDAYS][NUMBEROFHOTELS] = {};
    int tempEventsBooked1[NUMBEROFEVENTS] = {};

    int numberOfEventCombos;
    int percentage;
    //for each request order
    cout << "\nProgress: 0/" << requestCount << "\t\t";
    sortRequests();
    for(int r=0; r<requestCount; r++){
        //for each request in that order


        //ignore invalid requests
        if(!requests[r].getValid()) continue;

        //count events and calculate number of subsets aswell as earliest and latest event dates
        count = 0;
        best_singleProfit = -1;
        earliestEvent = NUMBEROFDAYS;
        latestEvent = -1;
        for(int e=0; e<NUMBEROFEVENTS; e++)
            if(requests[r].getEvents()[e]){
                count++;
                if(eventDateMap[e]<earliestEvent) earliestEvent = eventDateMap[e];
                if(eventDateMap[e]>latestEvent) latestEvent = eventDateMap[e];
            };

        numberOfEventCombos = pow(2,count+1);
        count = numberOfEventCombos*0.025;
        for(int e=0; e<numberOfEventCombos; e++){
            //for each subset of events

            //print progress
            if(e > count){
                cout << "|";
                count += numberOfEventCombos*0.025;
            }


            for(int fi=0; fi<=earliestEvent; fi++){
                //for each possible flyin date

                for(int fo=latestEvent; fo<NUMBEROFDAYS; fo++){
                    //for each possible flyout date
                    for(int h=0; h<pow(3,fo-fi); h++){
                        //For each possible hotel-type combination
                        //=========== create package =============

                        tempPackage = createPackageSmart(r, fi, fo, e, h, tempHotelsBooked, tempEventsBooked);
                        if(tempPackage.getTotalProfit() > best_singleProfit){
                            if(best_singleProfit>0) packages[r].clean();
                            packages[r] = createPackageSmart(r, fi, fo, e, h, tempHotelsBooked, tempEventsBooked);
                            best_singleProfit = tempPackage.getTotalProfit();
                            best_fi = fi;
                            best_fo = fo;

                            for(int i=0; i<NUMBEROFDAYS; i++)
                                for(int j=0; j<NUMBEROFHOTELS; j++)
                                    tempHotelsBooked1[i][j] =  tempHotelsBooked[i][j];

                            for(int i=0; i<NUMBEROFEVENTS; i++)
                                tempEventsBooked1[i] = tempEventsBooked[i];
                        }
                        tempPackage.clean();
                    }
                }
            }
        }
        //Update stats
        for(int i=0; i<NUMBEROFDAYS; i++)
        for(int j=0; j<NUMBEROFHOTELS; j++)
            hotelsBooked[i][j] = tempHotelsBooked1[i][j];

        for(int i=0; i<NUMBEROFEVENTS; i++) eventsBooked[i] = tempEventsBooked1[i];

        flyinsBooked[best_fi] += 1;
        flyoutBooked[best_fo] += 1;

        cout << "\nProgress: " << r+1 << "/" << requestCount << "\t\t";
    }
}

Package TravelAgent::createPackageSmart(int index, int fi, int fo, int eventNum, int hotelNum, int tempHotelsBooked[NUMBEROFDAYS][NUMBEROFHOTELS], int tempEventsBooked[NUMBEROFEVENTS]){
    //Create budget
    int budgetRemaining = requests[index].getBudget();

    //Create temp arrays
    bool EventsBool[NUMBEROFEVENTS] = {};

    //Fill temp arrays
    for(int i=0; i<NUMBEROFDAYS; i++)
        for(int j=0; j<NUMBEROFHOTELS; j++)
            tempHotelsBooked[i][j] = hotelsBooked[i][j];

    for(int i=0; i<NUMBEROFEVENTS; i++){
        tempEventsBooked[i] = eventsBooked[i];
        EventsBool[i] = requests[index].getEvents()[i];
    };

    //Get flights
    FlightTicket flights[2] = {FlightTicket(fi, FLIGHTPRICE, true),
                               FlightTicket(fo, FLIGHTPRICE, true)};
    for(int i=0; i<2; i++) budgetRemaining -= flights[i].getTicketPrice();
    if(budgetRemaining<0) return Package();

    //Get hotels
    HotelVoucher hotels[fo-fi] = {};
    int hotelType;
    for(int i=0; i<fo-fi; i++){
        hotelType = getBit(hotelNum, i+1, 3) ;
        //cout << "!" << hotelNum << "," << i << "," << hotelType << "!";
        hotels[i] = HotelVoucher(fi+i, hotelType+LOWESTSTARS, 100*tempHotelsBooked[i][hotelType]/hotelQuota[hotelType]);
        budgetRemaining -= hotels[i].getTicketPrice();
        tempHotelsBooked[fi+i][hotelType] += 1;
        if(tempHotelsBooked[fi+i][hotelType]>hotelQuota[hotelType] || budgetRemaining<0) return Package();
    }

    //Get events as bool array
    int count = 0;
    for(int i=0; i<NUMBEROFEVENTS; i++){
        if(EventsBool[i]){
            if(getBit(eventNum, count+1, 2)==0)
                EventsBool[i] = false;
            count++;
        }
    }

    //Get events
    EventTicket events[count] = {};
    count = 0;
    for(int i=0; i<NUMBEROFEVENTS; i++){
        if(EventsBool[i]){
            events[count] = EventTicket(i);
            tempEventsBooked[i] += 1;
            budgetRemaining -= events[count].getTicketPrice();
            count++;
            if(tempEventsBooked[i]>eventQuota[i] || budgetRemaining<0) return Package();
        }
    }

    //Return
    Package output = Package(flights, hotels, events, count);

    if(output.isfeasible()) return output;
    return Package();
}

int TravelAgent::getBit(int number, int bit, int base){ //returns true if the bit'th bit in the binary number is 1
    if(base==2){
        int c = 1 << (bit-1);
        if(number & c) return 1;
        return 0;
    }
    else{
        div_t divresult;
        for(int i=0; i<bit; i++){
            divresult = div(number,base);
            number = divresult.quot;
        }
        return divresult.rem;
    }
}

void TravelAgent::createPackageFirst(int index){
    //Check if valid
    if(!requests[index].getValid()) return;

    //Declarations
    int budgetRemaining = requests[index].getBudget();

    //Create temp arrays
    int tempHotelsBooked[NUMBEROFDAYS][NUMBEROFHOTELS] = {};
    int tempEventsBooked[NUMBEROFEVENTS] = {};

    for(int i=0; i<NUMBEROFDAYS; i++)
        for(int j=0; j<NUMBEROFHOTELS; j++)
            tempHotelsBooked[i][j] = hotelsBooked[i][j];

    for(int i=0; i<NUMBEROFEVENTS; i++) tempEventsBooked[i] = eventsBooked[i];

    //Flights
    FlightTicket flights[2] = {FlightTicket(requests[index].earliestEventDate(), FLIGHTPRICE, true),
                               FlightTicket(requests[index].latestEventDate(), FLIGHTPRICE, false)};
    for(int i=0; i<2; i++) budgetRemaining -= flights[i].getTicketPrice();

    //Hotels
    int found;
    HotelVoucher hotels[flights[1].getDate()-flights[0].getDate()] = {};
    for(int i=0; i<flights[1].getDate()-flights[0].getDate(); i++){
        found = 0;
        for(int h=0; h<NUMBEROFHOTELS; h++){
            if(tempHotelsBooked[i][h]>=hotelQuota[h]) continue;
            found = 1;
            hotels[i] = HotelVoucher(i, requests[index].getHotelType(), 100*tempHotelsBooked[i][h]/hotelQuota[h]);
            budgetRemaining -= hotels[i].getTicketPrice();
            tempHotelsBooked[i][h] += 1;
            break;
        }
        if(found==0) return; //leave invalid package if no available hotels are found
    }

    //Events
    EventTicket eventsTemp[NUMBEROFEVENTS] = {};
    EventTicket tempTicket;
    found = 0;
    for(int i=0; i<NUMBEROFEVENTS; i++){
        if(requests[index].getEvents()[i] && tempEventsBooked[i]<eventQuota[i] && found < MAXEVENTS){  //if wanted and within flight dates
            tempTicket = EventTicket(i);
            budgetRemaining -= tempTicket.getTicketPrice();

            if(budgetRemaining>0){
                eventsTemp[found] = tempTicket;
                tempEventsBooked[i] += 1;
                found += 1;
            }else{
                budgetRemaining += tempTicket.getTicketPrice();
            }
        }
    }
    if(found==0) return; //leave invalid package if no available events are found

    //get ciirect sized event array
    EventTicket events[found] = {};
    for(int i=0; i<found; i++)
        events[i] = eventsTemp[i];

    //Update stats
     for(int i=0; i<NUMBEROFDAYS; i++)
        for(int j=0; j<NUMBEROFHOTELS; j++)
            hotelsBooked[i][j] = tempHotelsBooked[i][j];

        for(int i=0; i<NUMBEROFEVENTS; i++)
            eventsBooked[i] = tempEventsBooked[i];

    flyinsBooked[flights[0].getDate()] += 1;
    flyoutBooked[flights[1].getDate()] += 1;


    //create packages
    packages[index] = Package(flights, hotels, events, found);
}

void TravelAgent::getRequests(bool genNew){
    string filePath = RequestGenerator::GenRequestList(genNew);

    ifstream myfile(filePath);
    if(!myfile.is_open()) throw "Error: No file found with path" + filePath;

    //Count feasible requests
    string line;
    requestCount = 0;
    while(getline(myfile,line))
        if(ClientRequest(1, line).getValid())
            requestCount++;

    //Set file to beginning
    myfile.clear();
    myfile.seekg(0, std::ios::beg);

    //Get feasible requests from file
    requests = new ClientRequest[requestCount];
    ClientRequest request;
    requestCount = 0;
    while(getline(myfile,line)){
        request = ClientRequest(requestCount, line);
        if(request.getValid()){
            requests[requestCount] = request;
            requestCount++;
        }
    }

    myfile.close();
}

int TravelAgent::getTotalProfit(){
    int output = 0;
    for(int i=0; i<requestCount; i++)
        if(packages[i].isfeasible())
            output += packages[i].getTotalProfit();
    return output;
}

//Public functions
void TravelAgent::printClients(){
    cout << "Client No\tbudget\thotel\tevents" << endl;

    bool first;
    for(int i=0; i<requestCount; i++){
        cout << "Client: " << i
             << "\t" << requests[i].getBudget()
             << "\t" << requests[i].getHotelType()
             << "\t";
        first = true;
        for (int j=0; j<NUMBEROFEVENTS; j++){
            if(requests[i].getEvents()[j]){
                if(!first) cout << " ";
                cout << j;
                first = false;
            }
        }
        cout << endl;
    }
}
void TravelAgent::printAll(){
    //Clients
    cout << "Read client requests .." << endl;
    printClients();
    cout << "Total client requests: " << requestCount << "\n" << endl;

    //Packages
    cout << "\nGenerate packages ...\n";
    for(int i=0; i<requestCount; i++){
        cout << "Client: " << i << " ";
        if(packages[i].isfeasible())
            cout << "Package generated successfully - client budget $"
                 << requests[i].getBudget() << " package cost $"
                 << packages[i].getTotalCost() << endl;
        else
            cout << "No sufficient budget or resources for this request." << endl;
    }

    //Valid packages
    cout << "\nGenerated valid packages : ";
    int n = 0;
    for(int i=0; i<requestCount; i++)
        if(packages[i].isfeasible()){
            cout << "\nClient: " << i << " ";
            packages[i].printAll();
            cout << endl;
            n++;
        }

    cout << "\nSummary of packages:\nTotal packages generated: "
         << n << endl;

    //stats
    cout << "\nTotal flyin tickets booked:\n";
    for(int i=0; i<NUMBEROFDAYS; i++)
        cout << flyinsBooked[i] << "  ";

    cout << "\nTotal flyout tickets booked:\n";
    for(int i=0; i<NUMBEROFDAYS; i++)
        cout << flyoutBooked[i] << "  ";

    cout << "\n\nTotal hotel vouchers sold:";
    for(int i=0; i<NUMBEROFHOTELS; i++){
        cout << "\n" << i+LOWESTSTARS
             << " star hotel rooms\n";
        for(int j=0; j<NUMBEROFDAYS; j++)
            cout << hotelsBooked[j][i] << "  ";
    }

    cout << "\n\nTotal event tickets sold:\n";
    for(int i=0; i<NUMBEROFEVENTS; i++)
        cout << eventsBooked[i] << "  ";

    cout << "\n\nTotal profit : $" << getTotalProfit() << endl;
}
