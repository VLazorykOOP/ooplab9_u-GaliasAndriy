#include "FitnessCenterData.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

FitnessCenterData::FitnessCenterData(int k) : client_code(k) {}

void FitnessCenterData::read_data(const string& filename) {
    ifstream input(filename);
    if (!input) {
        cerr << "Failed to open file " << filename << endl;
        return;
    }

    string line;
    while (getline(input, line)) {
        istringstream iss(line);
        Record r;
        iss >> r.duration >> r.year >> r.month >> r.client;
        data.push_back(r);
    }

    input.close();
}

void FitnessCenterData::process_data() {
    for (auto& each : data) {
        if (each.client == client_code) {
            auto it = by_year.find(each.year);
            if (it == by_year.end() || it->second->duration < each.duration) {
                by_year[each.year] = &each;
            }
            else if (it->second->duration == each.duration && each.month < it->second->month) {
                by_year[each.year] = &each;
            }
        }
    }
}

void FitnessCenterData::output_data() {
    if (by_year.empty()) {
        cout << "No data" << endl;
    }
    else {
        for (auto& it : by_year) {
            Record* each = it.second;
            cout << " | Year: " << each->year << " | Month: " << each->month << " | Duration(hs): "
                << each->duration << " | " << endl;
            cout << "------------------------------------------------" << endl;
        }
    }
}