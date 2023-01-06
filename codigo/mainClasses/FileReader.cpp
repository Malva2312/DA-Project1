//
// Created by andre on 30/03/22.
//

#include "FileReader.h"

FileReader::FileReader(){}

/**
 * Reads the information from the given dataset and creates a company with the couriers and packages from it
 * @param fileCouriers File containing the information of the couriers
 * @param filePackages File containing the information of the packages
 * @return company
 */
Company FileReader::readCompany(string fileCouriers, string filePackages){
    Company company;
    int id=0;
    vector<Courier> couriers;
    vector<Package> packages;
    map<int,Package> tempMap;

    ifstream file;
    file.open(fileCouriers);
    if (!file.is_open()){
        cout<<"courier file not found"<<endl;
    }

    string line;
    while(getline(file,line)){
        if (id==0){
            id+=1;
            continue;
        }
        stringstream str(line);
        string word;
        vector<string> row;
        while(getline(str,word,' ')){
            row.push_back(word);
        }
        Courier tempC(stoi(row[0]),stoi(row[1]),stoi(row[2]),id);
        couriers.push_back(tempC);
        id++;
    }
    file.close();

    id=0;
    file.open(filePackages);
    if (!file.is_open()){
        cout<<"package file not found"<<endl;
    }

    while(getline(file,line)) {
        if (id == 0) {
            id += 1;
            continue;
        }
        stringstream str(line);
        string word;
        vector<string> row;
        while (getline(str, word, ' ')) {
            row.push_back(word);
        }
        Package P1(stoi(row[0]), stoi(row[1]), stoi(row[2]), stof(row[3]), id);
        packages.push_back(P1);
        tempMap.insert({id,P1});
        id++;
    }
    company.setCouriers(couriers);
    company.setPackages(packages);
    company.setMap(tempMap);
    return company;
}

