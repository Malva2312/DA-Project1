//
// Created by andre on 17/04/22.
//

#include "App.h"

/**
 * Sets the company to be used inside of the user interface
 * @param comp company
 */
App::App(Company comp) {
    this->company=comp;
}
/**
 * Runs the user interface that allows the user to see all of the possible scenarios
 * @return 0 when the exit option is select
 */
int App::run() {
    int option;
    Company comp=getCompany();
    cout <<endl<< "Welcome to our warehouse!" << endl;
    while (true) {
        bool time= false;
        cout <<endl<< "Please choose what you would like to do"
             << endl << endl << "1. See the minimum number of couriers needed to fulfill all orders" << endl
             << "2. Similar to 1 but accounting for the duration" << endl << "3. See the maximum amount of profit that can be achieved" << endl
             << "4. Similar to 3 but accounting for the duration" << endl << "5. See the minimum average time to deliver the express packages in one day"<<endl
             << "6. See the average amount of packages each courier takes if split evenly"<< endl << "7. Select the ID of couriers to set them as unavailable" <<endl
             << "8. Reset the data"<<endl<< "9. Exit"<<endl;
        cin >> option;
        if (cin.fail()) {
            throw invalid_argument("Please choose a valid number");
        }
        switch (option) {
            case 1:
                if (comp.scenario1(time)){
                    comp.mapReset();
                }
                continue;
            case 2:
            {
                time= true;
                if(comp.scenario1(time)){
                    comp.mapReset();
                }
                continue;
            }
            case 3:
            {
                comp.scenario2(time);
                comp.mapReset();
                continue;
            }
            case 4:
                time= true;
                comp.scenario2(time);
                comp.mapReset();
                continue;
            case 5:
                if(comp.scenario3()){
                    comp.mapReset();
                }
                continue;
            case 6:
                if (comp.scenario4()){
                    comp.mapReset();
                }
                continue;
            case 7:{
                string end="notdone";
                int id;
                while (end!="done"){
                    cout<<endl<<"Enter the id to make it unavailable (Enter the word: <done> to end)"<<endl;
                    cin>>end;
                    stringstream convert(end);
                    convert>>id;
                    if (end!="done"&&id==0&&end!="0"){
                        cout<<"Please write a valid number or enter the word: <done> to end"<<endl;
                        continue;
                    }
                    if (id>0){
                        comp.setCourierUnavailable(id);
                    }
                }
                continue;
            }
            case 8:
                comp.mapReset();
                comp.availabilityReset();
                cout<<endl<<"The data has been reset"<<endl;
                continue;
            case 9:
                return 0;
            default:
                continue;
        }
    }
}


/**
 * Gets the company object inside of the app
 * @return company
 */
Company App::getCompany() {
    return this->company;
}
