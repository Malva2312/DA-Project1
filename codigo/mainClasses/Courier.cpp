//
// Created by andre on 30/03/22.
//

#include "Courier.h"
/**
 * Creates a courier with the given data
 * Note: The variable density in this case represents the sum of mass and volume unlike in the real world
 * @param maxVol maximum volume that the courier can handle
 * @param maxWeight maximum weight that the courier can handle
 * @param cost cost of the courier
 * @param id id of the courier
 */
Courier::Courier(int maxVol, int maxWeight, int cost, int id) : maxVol(maxVol), maxWeight(maxWeight), cost(cost),
                                                                id(id) {
    this->density=maxWeight+maxVol;
    this->available=true;
}

/**
 * Sets the courier maximum volume
 * @param maxVol
 */
void Courier::setMaxVol(int maxVol) {
    Courier::maxVol = maxVol;
}

/**
 * Sets the courier maximum weight
 * @param maxWeight
 */
void Courier::setMaxWeight(int maxWeight) {
    Courier::maxWeight = maxWeight;
}

/**
 * Sets the courier cost
 * @param cost
 */
void Courier::setCost(int cost) {
    Courier::cost = cost;
}

/**
 * Gets the maximum volume that the courier can handle
 * @return maximum volume
 */
int Courier::getMaxVol() const {
    return maxVol;
}

/**
 * Gets the maximum weight that the courier can handle
 * @return maximum weight
 */
int Courier::getMaxWeight() const {
    return maxWeight;
}

/**
 * Gets the cost of the courier
 * @return cost
 */
int Courier::getCost() const {
    return cost;
}

/**
 * Sets the id of the courier
 * @param id
 */
void Courier::setId(int id) {
    Courier::id = id;
}

/**
 * Gets the id of the courier
 * @return id
 */
int Courier::getId() const {
    return id;
}

/**
 * Overloads the courier operator to later sort them
 * @param courier
 * @return
 */
bool Courier::operator<(Courier courier) {
    return this->density>courier.getDensity();
}

/**
 * Gets the courier density
 * @return density
 */
float Courier::getDensity() const {
    return density;
}

/**
 * Sets the courier density
 * @param density
 */
void Courier::setDensity(float density) {
    Courier::density = density;
}

/**
 * Adds a package to the vector of packages inside of the courier
 * @param P package
 */
void Courier::addPackage(Package P) {
    this->packages.push_back(P);
}

/**
 * Returns the vector of packages
 * @return packages
 */
vector<Package> Courier::getPackages() {
    return this->packages;
}

/**
 * Sets the availability of the courier
 * @param available
 */
void Courier::setAvailable(bool available) {
    Courier::available = available;
}

/**
 * Checks whether the courier is available or not
 * @return available
 */
bool Courier::isAvailable() const {
    return available;
}


