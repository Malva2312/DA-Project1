//
// Created by andre on 17/04/22.
//

#ifndef P1_APP_H
#define P1_APP_H


#include "mainClasses/Company.h"
#include <sstream>

class App {
public:
    App(Company comp);
    int run();
    Company getCompany();

private:
    Company company;
};


#endif //P1_APP_H
