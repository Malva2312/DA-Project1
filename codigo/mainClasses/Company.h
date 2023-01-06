//
// Created by andre on 30/03/22.
//

#ifndef P1_COMPANY_H
#define P1_COMPANY_H
#include <vector>
#include "Courier.h"
#include "Package.h"
#include <iostream>
#include <map>

using namespace std;

class Company {
public:
    void setCouriers(vector<Courier> couriers);
    void setPackages(vector<Package> packages);
    void setMap(map<int,Package> pMap);
    bool scenario1(bool time);
    void scenario2(bool time);
    bool scenario3();
    bool scenario4();
    void mapReset();
    void availabilityReset();
    void test(vector<Courier> tempCouriers);
    void setCourierUnavailable(int id);

private:
    vector<Courier> couriers;
    vector<Package> packages;
    map<int,Package> packagesMap;
};


#endif //P1_COMPANY_H
