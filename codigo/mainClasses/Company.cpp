//
// Created by andre on 30/03/22.
//

#include <algorithm>
#include "Company.h"
#include <iomanip>
#include <cmath>

/**
 * Sets the vector of couriers
 * @param couriers
 */
void Company::setCouriers(vector<Courier> couriers) {
    this->couriers=couriers;
}

/**
 * Sets the vector of packages
 * @param packages
 */
void Company::setPackages(vector<Package> packages) {
    this->packages=packages;
}

/**
 * Displays the minimum number of couriers necessary to deliver all packages as well as the profit and efficiency
 * Sorts the couriers by density and if possible gives the courier the package with most mass or volume depending on whether they have more volume or mass
 * If the value of "time" is true then it will account for the duration variable of each package
 * When a package is added to a courier then it is set as "done" in the company's map of packages
 * @param time
 * @return true if every package was delivered, false otherwise
 */
bool Company::scenario1(bool time) {
    vector<Courier> tempCourier;
    for (int i=0;i<couriers.size();i++){
        if (couriers[i].isAvailable()){
            tempCourier.push_back(couriers[i]);
        }
    }
    vector<Package> tempPMass=packages;
    vector<Package> tempPVol=packages;
    vector<Courier> decision;
    int size = packages.size();
    for (auto &it: packagesMap){
        if (it.second.isDone()){
            size-=1;
        }
    }
    int profit=0;
    double efficiency;
    int counter=0;
    sort(tempCourier.begin(),tempCourier.end());
    sort(tempPMass.begin(),tempPMass.end(), [](Package A, Package B){
        return A.getWeight()>B.getWeight();
    });
    sort(tempPVol.begin(),tempPVol.end(), [](Package A, Package B){
        return A.getVolume()>B.getVolume();
    });

    for (int i=0;i< tempCourier.size();i++){
        float hours=8;
        int reward=0;
        bool fullCheck=true;
        bool allDone=true;
        while(fullCheck){
            fullCheck=false;
            if (tempCourier[i].getMaxVol()>tempCourier[i].getMaxWeight()){
                for (int j=0;j<tempPVol.size();j++){
                    auto it=packagesMap.find(tempPVol[j].getId());
                    if (tempCourier[i].getMaxVol()-tempPVol[j].getVolume()>=0&&!it->second.isDone()&&tempCourier[i].getMaxWeight()-tempPVol[j].getWeight()>=0){
                        if (time && hours-tempPVol[j].getDuration()<0){
                            continue;
                        }
                        tempCourier[i].setMaxVol(tempCourier[i].getMaxVol()-tempPVol[j].getVolume());
                        tempCourier[i].setMaxWeight(tempCourier[i].getMaxWeight()-tempPVol[j].getWeight());
                        reward+=tempPVol[j].getReward();
                        tempCourier[i].addPackage(tempPVol[j]);
                        fullCheck=true;
                        hours-=tempPVol[j].getDuration();
                        it->second.setDone(true);
                        counter+=1;
                        break;
                    }
                }
            }
            else{
                for (int j=0;j<tempPMass.size();j++){
                    auto it=packagesMap.find(tempPMass[j].getId());
                    if (tempCourier[i].getMaxWeight()-tempPMass[j].getWeight()>=0&&!it->second.isDone()&&tempCourier[i].getMaxVol()-tempPMass[j].getVolume()>=0){
                        if (time && hours-tempPMass[j].getDuration()<0){
                            continue;
                        }
                        tempCourier[i].setMaxWeight(tempCourier[i].getMaxWeight()-tempPMass[j].getWeight());
                        tempCourier[i].setMaxVol(tempCourier[i].getMaxVol()-tempPMass[j].getVolume());
                        reward+=tempPMass[j].getReward();
                        tempCourier[i].addPackage(tempPMass[j]);
                        fullCheck= true;
                        hours-=tempPMass[j].getDuration();
                        it->second.setDone(true);
                        counter+=1;
                        break;
                    }
                }
            }
        }
        for (auto &it: packagesMap){
            if (!it.second.isDone()){
                allDone= false;
            }
        }
        profit+=(reward-tempCourier[i].getCost());
        decision.push_back(tempCourier[i]);
        if (allDone){
            break;
        }
    }
    efficiency=((double)counter/(double)size)*100;
    cout<<endl<<"Minimum number of couriers needed: "<<decision.size()<<" | Efficiency: "<<setprecision(2)<<fixed<<efficiency<<"%"<<endl;
    cout<<"Profit: "<<profit<<endl;
    if (counter!=size){
        cout<<endl<<"Not all packages were able to be delivered"<<endl<<endl;
        return false;
    }
    return true;
}

/**
 * Sets the map of packages
 * @param pMap Packages map
 */
void Company::setMap(map<int,Package> pMap) {
    this->packagesMap= pMap;
}

/**
 * Displays the maximum profit that the company can achieve as well as the number of couriers, the number of discarded packages and the efficiency
 * Sorts the couriers by the relation between density and their cost and if possible gives the courier the package with most mass or volume depending on whether they have more volume or mass
 * If the value of "time" is true then it will account for the duration variable of each package
 * When a package is added to a courier then it is set as "done" in the company's map of packages
 * If the reward of some packages is bellow a minimum value that signifies that the package itself isn't worth to deliver then it will be discarded which allows to not use so many couriers and improve the profit
 * @param time
 */
void Company::scenario2(bool time) {
    mapReset();
    vector<Courier> tempCourier;
    double sum;
    double sum2;
    int minimum;
    int profit=0;
    double efficiency;
    int counter=0;
    int discarded=0;
    vector<Package> tempPackages = packages;
    vector<Package> tempPMass;
    vector<Package> tempPVol;
    vector<Courier> decision;
    for (int i=0;i<tempPackages.size();i++){
        sum2+=tempPackages[i].getReward();
    }
    for (int i=0;i<couriers.size();i++){
        if (couriers[i].isAvailable()){
            sum+=couriers[i].getCost();
            tempCourier.push_back(couriers[i]);
        }
    }
    sum = sum / (double) tempCourier.size();
    sum2 = sum2 / (double) tempPackages.size();
    minimum = floor((sum2/sum)*0.5*sum);
    for (int i=0;i<tempPackages.size();i++){
        if (tempPackages[i].getReward()>=minimum){
            tempPMass.push_back(tempPackages[i]);
            tempPVol.push_back(tempPackages[i]);
        }
        else{
            discarded+=1;
        }
    }
    int size = tempPMass.size();
    for (auto &it: packagesMap){
        if (it.second.isDone()){
            size-=1;
        }
    }
    sort(tempCourier.begin(),tempCourier.end(),[](Courier A, Courier B){
        return (A.getCost()/A.getDensity())<(B.getCost()/B.getDensity());
    });

    sort(tempPMass.begin(),tempPMass.end(), [](Package A, Package B){
        return A.getWeight()>B.getWeight();
    });
    sort(tempPVol.begin(),tempPVol.end(), [](Package A, Package B){
        return A.getVolume()>B.getVolume();
    });

    for (int i=0;i< tempCourier.size();i++){
        float hours=8;
        int reward=0;
        bool fullCheck=true;
        while(fullCheck){
            fullCheck=false;
            if (tempCourier[i].getMaxVol()>tempCourier[i].getMaxWeight()){
                for (int j=0;j<tempPVol.size();j++){
                    auto it=packagesMap.find(tempPVol[j].getId());
                    if (tempCourier[i].getMaxVol()-tempPVol[j].getVolume()>=0&&!it->second.isDone()&&tempCourier[i].getMaxWeight()-tempPVol[j].getWeight()>=0){
                        if (time && hours-tempPVol[j].getDuration()<0){
                            continue;
                        }
                        tempCourier[i].setMaxVol(tempCourier[i].getMaxVol()-tempPVol[j].getVolume());
                        tempCourier[i].setMaxWeight(tempCourier[i].getMaxWeight()-tempPVol[j].getWeight());
                        reward+=tempPVol[j].getReward();
                        tempCourier[i].addPackage(tempPVol[j]);
                        fullCheck=true;
                        hours-=tempPVol[j].getDuration();
                        it->second.setDone(true);
                        counter+=1;

                        break;
                    }
                }
            }
            else{
                for (int j=0;j<tempPMass.size();j++){
                    auto it=packagesMap.find(tempPMass[j].getId());
                    if (tempCourier[i].getMaxWeight()-tempPMass[j].getWeight()>=0&&!it->second.isDone()&&tempCourier[i].getMaxVol()-tempPMass[j].getVolume()>=0){
                        if (time && hours-tempPMass[j].getDuration()<0){
                            continue;
                        }
                        tempCourier[i].setMaxWeight(tempCourier[i].getMaxWeight()-tempPMass[j].getWeight());
                        tempCourier[i].setMaxVol(tempCourier[i].getMaxVol()-tempPMass[j].getVolume());
                        reward+=tempPMass[j].getReward();
                        tempCourier[i].addPackage(tempPMass[j]);
                        fullCheck= true;
                        hours-=tempPMass[j].getDuration();
                        it->second.setDone(true);
                        counter+=1;
                        break;
                    }
                }
            }
        }
        profit+=(reward-tempCourier[i].getCost());
        decision.push_back(tempCourier[i]);
        if (counter==tempPMass.size()){
            break;
        }

    }
    efficiency=((double)counter/(double)size)*100;
    cout<<endl<<"Minimum number of couriers needed: "<<decision.size()<<" | Efficiency: "<<setprecision(2)<<fixed<<efficiency<<"%"<<endl;
    cout<<"Profit: "<<profit<<endl;
    if (discarded>0){
        cout<<endl<<"To maximize profit, "<<discarded<<" packages were discarded"<<endl;
    }
}

/**
 * Resets the map of pakcages so that every package is considered as undelivered
 */
void Company::mapReset() {
    for (auto &it: packagesMap){
        it.second.setDone(false);
    }

}

/**
 * Displays the minimum average time to deliver all of the express packages as well as the efficiency
 * Note: to better show the logic behind this scenario we considered every package in the dataset as an express one which means not all of them will be delivered in one day and since they return to the company, they will keep on being delivered in the following days
 * Sorts the packages in ascending order of duration which is what minimizes the average time (Same logic as exercise 7 of the first practical class)
 * Since the packages are sorted in ascending order each day less packages will be delivered and the minimum average time will rise
 * @return true if every package was delivered, false otherwise
 */
bool Company::scenario3() {
    vector<Package> tempPackages;
    for (int i=0;i<packages.size();i++){
        auto it=packagesMap.find(packages[i].getId());
        if (!it->second.isDone()){
            tempPackages.push_back(it->second);
        }
    }
    sort(tempPackages.begin(),tempPackages.end(), [] (Package A, Package B){
        return A.getDuration()<B.getDuration();
    });
    int size = tempPackages.size();
    float hours=8;
    double average=0;
    int counter=0;
    double efficiency;
    for (int i=0;i<tempPackages.size();i++){
        auto it=packagesMap.find(tempPackages[i].getId());
        if (hours-tempPackages[i].getDuration()<0){
            break;
        }
        counter+=1;
        hours-=tempPackages[i].getDuration();
        it->second.setDone(true);
    }
    for (int i=0;i<counter;i++){
        average+=tempPackages[i].getDuration()*(double)(counter-i);
    }
    average=average/counter;
    efficiency=((double)counter/(double)size)*100;
    cout<<endl<<"Minimum average: "<<fixed<<setprecision(2)<<average<<" hours | "<<counter<<" out of "<<tempPackages.size()<<" packages delivered"<<" | Efficiency: "<<fixed<<setprecision(2)<<efficiency<<"%"<<endl;
    if (counter!=size){
        cout<<endl<<"Not all packages were able to be delivered"<<endl<<endl;
        return false;
    }
    return true;
}

/**
 * Test function that determines whether or not the couriers could actually take the packages they were given
 * Not being used at the moment, only present for testing purposes
 * @param tempCouriers vector of the chosen couriers
 */
void Company::test(vector<Courier> tempCouriers) {
    vector<int> temp;
    for (int i=0; i<tempCouriers.size();i++){
        cout<<"volLeft: "<<tempCouriers[i].getMaxVol()<<" MassLeft: "<<tempCouriers[i].getMaxWeight()<<" nªPackages: "<<tempCouriers[i].getPackages().size()<<endl;
        int tempV=0;
        int tempM=0;
        for (int j=0; j<tempCouriers[i].getPackages().size();j++){
            for (int k=0;k<temp.size();k++){
                if (temp[k]==tempCouriers[i].getPackages()[j].getId()){
                    cout<<"error"<<endl;
                }
            }

            temp.push_back(tempCouriers[i].getPackages()[j].getId());
            tempV+=tempCouriers[i].getPackages()[j].getVolume();
            tempM+=tempCouriers[i].getPackages()[j].getWeight();

        }
        for (int l=0;l<couriers.size();l++){
            if (tempCouriers[i].getId()==couriers[l].getId()){
                cout<<tempCouriers[i].getId()<<" "<<couriers[l].getId()<<endl;
                if (tempV+tempCouriers[i].getMaxVol()!=couriers[l].getMaxVol() || tempM+tempCouriers[i].getMaxWeight()!=couriers[l].getMaxWeight()){
                    cout<<"error"<<endl;
                }
            }
        }
    }
}

/**
 * Displays the average number of packages each courier take if they are split evenly between all of them as well as the number of couriers needed and the efficiency
 * Gives one package to each courier at a time so that they all have the same amount
 * @return true if all of the packages were delivered, false otherwise
 */
bool Company::scenario4() {
    vector<Courier> tempCourier;
    for (int i=0;i<couriers.size();i++){
        if (couriers[i].isAvailable()){
            tempCourier.push_back(couriers[i]);
        }
    }
    vector<Package> tempPackage;
    int size = packages.size();
    for (auto &it: packagesMap){
        if (it.second.isDone()){
            size-=1;
        }
        else{
            tempPackage.push_back(it.second);
        }
    }
    double efficiency;
    int counter=0;
    sort(tempCourier.begin(),tempCourier.end());
    sort(tempPackage.begin(),tempPackage.end(), [](Package A, Package B){
       return (A.getWeight()+A.getVolume())>(B.getWeight()+B.getVolume());
    });
    int total=size;
    while (total>0){
        bool added=false;
        for (int i=0;i<tempCourier.size();i++){
            for (int j=0;j<tempPackage.size();j++){
                auto it=packagesMap.find(tempPackage[j].getId());
                if (tempCourier[i].getMaxWeight()-tempPackage[j].getWeight()>=0&&tempCourier[i].getMaxVol()-tempPackage[j].getVolume()>=0&&!it->second.isDone()){
                    tempCourier[i].setMaxWeight(tempCourier[i].getMaxWeight()-tempPackage[j].getWeight());
                    tempCourier[i].setMaxVol(tempCourier[i].getMaxVol()-tempPackage[j].getVolume());
                    counter+=1;
                    total-=1;
                    it->second.setDone(true);
                    tempCourier[i].addPackage(tempPackage[j]);
                    added=true;
                    break;
                }
            }
        }
        if (!added){
            break;
        }
    }
    int distribution = floor(counter/tempCourier.size());
    bool allDelivered=true;
    for (auto &it: packagesMap){
        if (!it.second.isDone()){
            allDelivered=false;
        }
    }

    efficiency=((double)counter/(double)size)*100;
    cout<<endl<<"Number of couriers needed: "<<tempCourier.size()<<" | Efficiency: "<<setprecision(2)<<fixed<<efficiency<<"%"<<endl;
    cout<<"Each courier is carrying an average of : "<<distribution<<" packages"<<endl;
    if (!allDelivered){
        cout<<endl<<"Not all packages were able to be delivered"<<endl<<endl;
        return false;
    }
    return true;

}


/**
 * Resets the availability by setting each courier as available
 */
void Company::availabilityReset() {
    for (int i=0;i<couriers.size();i++){
        couriers[i].setAvailable(true);
    }
}

/**
 * Sets the courier with the given id as unavailable
 * @param id
 */
void Company::setCourierUnavailable(int id) {
    for (int i=0;i<couriers.size();i++){
        if (couriers[i].getId()==id){
            couriers[i].setAvailable(false);
            cout<<endl<<"The courier with id: "<<couriers[i].getId()<<" has been set as unavailable"<<endl<<endl;
            break;
        }
    }
}


