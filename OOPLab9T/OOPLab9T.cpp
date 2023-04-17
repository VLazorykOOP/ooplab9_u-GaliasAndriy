#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

class FitnessCenterData {
private:
    struct Record {
        int duration;
        int year;
        int month;
        int client;
    };

    int client_code;
    vector<Record> data;
    map<int, Record*, less<int>> by_year;

public:
    FitnessCenterData(int k) : client_code(k) {}

    void read_data(const string& filename) {
        ifstream input(filename);
        if (!input) {
            cerr << "Failed to open file " << filename << endl;
            return;
        }

        string line;
        while (getline(input, line)) {
            istringstream iss(line); // read each linea as a string
            Record r;
            iss >> r.duration >> r.year >> r.month >> r.client; // sequence 
            data.push_back(r);
        }

        input.close();
    }

    void process_data() {
        for (auto& each : data) {
            if (each.client == client_code) { // check all the data of specific client
                auto it = by_year.find(each.year); // we'll check max duration for each year
                if (it == by_year.end() || it->second->duration < each.duration) {
                    by_year[each.year] = &each;
                }
                else if (it->second->duration == each.duration && each.month < it->second->month) {
                    by_year[each.year] = &each;
                }
            }
        }
    }

    void output_data() {
        if (by_year.empty()) {
            cout << "No data" << endl;
        }
        else {
            // using methods rbegin() and rend() give us an opportunity to sort a map ascendant order
            for (auto& it : by_year) { // rbegin() - reversed begin (end) 
                Record* each = it.second;
                cout << " | Year: " << each->year << " | Month: " << each->month << " | Duration(hs): " 
                    << each->duration << " | " << endl;
                cout << "------------------------------------------------" << endl;
            }
        }
    }
};

int main() {
    int k;
    cout << "Enter client code: ";
    cin >> k;

    FitnessCenterData data(k);

    cout << "\n Client [" << k << "] data:" << endl;
    cout << "------------------------------------------------" << endl;
    data.read_data("test.txt");
    data.process_data();
    data.output_data();

    return 0;
}