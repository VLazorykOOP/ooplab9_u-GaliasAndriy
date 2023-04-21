#include "FitnessCenterData.h"
#include "Vector.h"
#include "Assoc7.h"
#include <iostream>
using namespace std;

int main() {
    int choice;
    cout << "Lab 9" << endl;
    cout << "  Please select an option:" << endl;
    cout << "  1. Task 1 - Fitness center" << endl;
    cout << "  2. Task 2 - Vector" << endl;
    cout << "  3. Task 3 - 2 Vectors Assoc" << endl;
    cout << "  Enter your choice: ";
    cin >> choice;

    FitnessCenterData data(0); 
    int k; 
    switch (choice) {
    case 1:
        cout << "\n Enter client code: ";
        cin >> k;

        data = FitnessCenterData(k); // initialize with user input
        cout << "\n Client [" << k << "] data:" << endl;
        cout << "------------------------------------------------" << endl;
        data.read_data("test.txt");
        data.process_data();
        data.output_data();
        break;
    case 2:
        cout << "Task 2" << endl;
        findFirstOfVector();
        break;
    case 3: 
        cout << "Task 3" << endl;
        findValuesWhichAbsentInAnotherVector();
        break;
    default:
        cout << "Wrong input!" << endl;
    }
    return 0;
}