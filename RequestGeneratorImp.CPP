#include "RequestGenerator.H"
#include "Constants.h"
#include <fstream>
#include <random>
#include <time.h>
#include <algorithm>
#include <array>

#include <iostream>

using namespace std;

string RequestGenerator::GenRequestList(bool genNew){
    //Check if default wanted
    if(!genNew) return "requestLists/requestlist.txt";

    //Declarations
    mt19937 rng(time(NULL));
    int requestCount = getRandomBetween(MINREQUESTS, MAXREQUESTS, rng);
    string filePath = "requestLists/requestlist-" + getTimeStamp() + ".txt";

    //write file
    ofstream myfile;
    myfile.open(filePath);
    string newline = "\n";
    for(int i=0; i<requestCount; i++){
        if(i>=requestCount-1) newline == "";
        myfile << getSingleRequest(rng) << newline;
    }
    myfile.close();

    //return
    return filePath;
}

string RequestGenerator::getTimeStamp(){
    static char stamp[16];
    time_t now = time(0);
    strftime(stamp, 16, "%Y%m%d_%H%M%S", localtime(&now));
    return stamp;
}

string RequestGenerator::getSingleRequest(mt19937& seed){
    //Declarations
    int eventCount = getRandomBetween(1, MAXEVENTS, seed);
    string output = "";

    //Get all events in random order
    array<int, NUMBEROFEVENTS> allEvents;  //Get an array of all possible events
    iota(allEvents.begin(), allEvents.end(), 0);
    random_shuffle(std::begin(allEvents), std::end(allEvents)); //Randomizse list of events

    //Get budget
    int budgetType = 0;
    for(int i=0; i<eventCount; i++){
        if(nameMap[allEvents[i]] == "Opening") budgetType += 2;
        if(nameMap[allEvents[i]] == "Closing") budgetType += 1;
    }

    if(budgetType>1) output += to_string(getRandomBetween(
                                              4500+150*eventCount,
                                              7500+150*eventCount, seed));
    else if (budgetType==1) output += to_string(getRandomBetween(
                                              3800+150*eventCount,
                                              6800+150*eventCount, seed));
    else output += to_string(getRandomBetween(3250+150*eventCount,
                                              5250+150*eventCount, seed));
    output += ",";

    //Get hotel
    output += to_string(getRandomBetween(LOWESTSTARS, 5, seed)) + "[";

    //Get events - get the first eventcount elements of the array containing all events in a random order
    for(int i=0; i<eventCount; i++){
        if(i>0) output += ",";
        output += to_string(allEvents[i]);
    }

    return output + "]";
}

int RequestGenerator::getRandomBetween(int a, int b, mt19937& seed){
    //Fix data if inputted wrong
    if(a>b) swap(a,b);

    //Unbiased random
    uniform_int_distribution<int> gen(a, b);
    return gen(seed);
}
