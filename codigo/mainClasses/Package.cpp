//
// Created by andre on 30/03/22.
//

#include "Package.h"

/**
 * Creates a package with the given data
 * The duration is converted to hours
 * Every package is set an undelivered by default
 * @param volume volume of the package
 * @param weight weight of the package
 * @param reward reward given upon delivery
 * @param duration time in seconds that it takes to deliver and return
 * @param id package id
 */
Package::Package(int volume, int weight, int reward, float duration, int id) : volume(volume), weight(weight),
                                                                             reward(reward),
                                                                             id(id) {
    this->done= false;
    this->duration=duration/3600;
}


/**
 * Sets the package volume
 * @param volume
 */
void Package::setVolume(int volume) {
    Package::volume = volume;
}

/**
 * Sets the package weight
 * @param weight
 */
void Package::setWeight(int weight) {
    Package::weight = weight;
}

/**
 * Sets the package reward
 * @param reward
 */
void Package::setReward(int reward) {
    Package::reward = reward;
}

/**
 * Sets the package duration
 * @param duration
 */
void Package::setDuration(int duration) {
    Package::duration = duration;
}

/**
 * returns the package volume
 * @return volume
 */
int Package::getVolume() const {
    return volume;
}

/**
 * returns the package weight
 * @return weight
 */
int Package::getWeight() const {
    return weight;
}

/**
 * returns the package reward
 * @return reward
 */
int Package::getReward() const {
    return reward;
}

/**
 * returns the package duration
 * @return duration
 */
float Package::getDuration() const {
    return duration;
}

/**
 * Sets the package id
 * @param id
 */
void Package::setId(int id) {
    Package::id = id;
}

/**
 * returns the package id
 * @return id
 */
int Package::getId() const {
    return id;
}

/**
 * Checks if the package has been delivered
 * @return done
 */
bool Package::isDone() const {
    return done;
}

/**
 * Sets a package as delivered
 * @param done
 */
void Package::setDone(bool done) {
    Package::done = done;
}



