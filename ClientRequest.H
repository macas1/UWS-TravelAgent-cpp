#ifndef CLIENTREQUEST_H_
#define CLIENTREQUEST_H_
#include "Constants.h"
//
class ClientRequest {
private:
    int cId;
	int hotelType;
	int budget;
    bool events[NUMBEROFEVENTS];
    bool valid;
    string* split(string s, char delimteter, int& length, int max);
public:
    //Constructors
	ClientRequest();
	ClientRequest(int id, int ht, int b, bool e[NUMBEROFEVENTS]);
	ClientRequest(int id, string input);

	//Getters
	int getId() const;
	int getHotelType() const;
	int getBudget() const;
	bool* getEvents();
	bool getValid() const;


	//Functions
	int earliestEventDate();
	int latestEventDate();
	void print();
	void reject();
};

#endif /* CLIENTREQUEST_H_ */
