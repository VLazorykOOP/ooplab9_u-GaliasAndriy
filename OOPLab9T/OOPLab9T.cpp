//#include <iostream>
//#include <vector>
//#include <algorithm>
//using namespace std;
//
//struct Entry {
//    int duration;
//    int year;
//    int month;
//    int client_code;
//};
//
//class FitnessCenter {
//private:
//    vector<Entry> sequence;
//public:
//    void add_client(int duration, int year, int month, int client_code) {
//        if (sequence.size() >= 50) {
//            cout << "Error: There cannot be more than 50 clients" << endl;
//            return;
//        }
//        sequence.push_back({ duration, year, month, client_code }); // push clients with proper fields
//    }
//
//    void remove_client(int index) {
//        if (index < 0 || index >= sequence.size()) {
//            cout << "Error: invalid index." << endl;
//            return;
//        }
//        sequence.erase(sequence.begin() + index);
//    }
//
//    int get_clients() {
//        sort(sequence.begin(), sequence.end(),
//            [](const Entry& a, const Entry& b) {
//                return a.client_code < b.client_code;
//            }); // sorting clients based on their client_code
//        int num_clients = 0;
//        for (int i = 0; i < sequence.size(); i++) {
//            if (i == 0 || sequence[i].client_code != sequence[i - 1].client_code) {
//                num_clients++; // count clients 
//            }
//        }
//        return num_clients;
//    }
//
//    void print_sequence() {
//        for (int i = 0; i < sequence.size(); i++) {
//            cout << sequence[i].duration << " " << sequence[i].year << " " << sequence[i].month
//                << " " << sequence[i].client_code << endl;
//        }
//    } // for printing every client and its info
//
//    void printMaxDurationMonth(int client_code) { // search specific client and max duration month of this client
//        vector<int> years;
//        for (int i = 0; i < sequence.size(); i++) {
//            if (sequence[i].client_code == client_code) {
//                bool year_found = find(years.begin(), years.end(), sequence[i].year) != years.end();
//                if (!year_found) {
//                    years.push_back(sequence[i].year);
//                }
//            }
//        }
//        sort(years.begin(), years.end());
//
//        for (int i = 0; i < years.size(); i++) {
//            int max_duration = -1;
//            int max_month = -1;
//            for (int month = 1; month <= 12; month++) {
//                int total_duration = 0;
//                for (int j = 0; j < sequence.size(); j++) {
//                    if (sequence[j].client_code == client_code &&
//                        sequence[j].year == years[i] &&
//                        sequence[j].month == month) {
//                        total_duration += sequence[j].duration;
//                    }
//                }
//                if (total_duration > max_duration) {
//                    max_duration = total_duration;
//                    max_month = month;
//                }
//            }
//            cout << "Year " << years[i] << ", month " << max_month << ", max duration " << max_duration << endl;
//        }
//    }
//};
//
//int main () {
//    FitnessCenter center;
//
//    // Adding clients
//    center.add_client(60, 2022, 3, 1);
//    center.add_client(30, 2022, 3, 2);
//    center.add_client(30, 2022, 4, 3);
//    center.add_client(60, 2022, 5, 2);
//    center.add_client(61, 2022, 7, 2);
//    center.add_client(30, 2022, 7, 4);
//    center.add_client(30, 2022, 7, 2);
//    center.add_client(105, 2022, 7, 5);
//    center.add_client(60, 2022, 8, 1);
//    center.add_client(30, 2022, 8, 2);
//    center.add_client(60, 2022, 8, 3);
//    center.add_client(60, 2022, 9, 4);
//    center.add_client(30, 2022, 9, 5);
//    center.add_client(60, 2022, 9, 1);
//    center.add_client(60, 2022, 10, 2);
//
//    // Print the clients' information
//    center.print_sequence();
//
//    // Get the number of clients
//    cout << "Number of clients: " << center.get_clients() << endl;
//
//    // Remove a client
//    cout << "\n\n";
//    center.remove_client(2);
//
//    // Print the clients' information again
//    center.print_sequence();
//
//    // Get the number of clients again
//    cout << "Number of clients: " << center.get_clients() << endl;
//
//    // Print the max duration month for a client
//    center.printMaxDurationMonth(5);
//
//    return 0;
//}

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
    map<int, Record*, greater<int>> by_year;

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
            for (auto it = by_year.rbegin(); it != by_year.rend(); ++it) { // rbegin() - reversed begin (end) 
                Record* each = it->second;
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