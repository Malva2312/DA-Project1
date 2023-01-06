//
// Created by andre on 30/03/22.
//

#ifndef P1_FILEREADER_H
#define P1_FILEREADER_H
#include "Company.h"
#include "Courier.h"
#include "Package.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

class FileReader {
public:
    FileReader();
    Company readCompany(string fileCouriers, string filePackages);
};


#endif //P1_FILEREADER_H
