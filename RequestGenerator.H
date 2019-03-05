#include "ClientRequest.H"
#include <random>

class RequestGenerator {
public:
    static string GenRequestList(bool genNew);
    static string getTimeStamp();
    static string getSingleRequest(mt19937& seed);
    static int getRandomBetween(int a, int b, mt19937& seed);
};
