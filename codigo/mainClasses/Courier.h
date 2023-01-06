//
// Created by andre on 30/03/22.
//

#ifndef P1_COURIER_H
#define P1_COURIER_H


#include "Package.h"
#include <vector>
using namespace std;

class Courier {
public:
    Courier(int maxVol, int maxWeight, int cost, int id);

    void setMaxVol(int maxVol);

    void setMaxWeight(int maxWeight);

    void setCost(int cost);

    void setId(int id);

    void setDensity(float density);

    void setAvailable(bool available);

    int getMaxVol() const;

    int getMaxWeight() const;

    int getCost() const;

    int getId() const;

    float getDensity() const;

    bool isAvailable() const;

    bool operator < (Courier courier);

    void addPackage(Package P);

    vector<Package> getPackages();

private:
    int maxVol, maxWeight, cost, id;
    float density;
    vector<Package> packages;
    bool available;
};


#endif //P1_COURIER_H
