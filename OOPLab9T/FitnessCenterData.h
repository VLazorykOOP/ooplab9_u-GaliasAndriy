#pragma once

#ifndef FITNESS_CENTER_DATA_H
#define FITNESS_CENTER_DATA_H

#include <string>
#include <vector>
#include <map>

class FitnessCenterData {
private:
    struct Record {
        int duration;
        int year;
        int month;
        int client;
    };
    int client_code;
    std::vector<Record> data;
    std::map<int, Record*, std::less<int>> by_year;

public:
    FitnessCenterData(int k);
    void read_data(const std::string& filename);
    void process_data();
    void output_data();
};

#endif