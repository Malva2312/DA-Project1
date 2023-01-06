#include <iostream>
#include "mainClasses/FileReader.h"
#include "App.h"

int main() {
    string fileCouriers = "../../input/carrinhas.txt";
    string filePackages = "../../input/encomendas.txt";

    FileReader fileReader;

    App app(fileReader.readCompany(fileCouriers, filePackages));
    app.run();

    return 0;
}
