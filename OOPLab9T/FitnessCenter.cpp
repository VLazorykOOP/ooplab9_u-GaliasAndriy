#include "FitnessCenter.h"

void FitnessCenter::processClientData(int clientCode) {
	ifstream input(map_filename);
	if (!input) {
		try {
			throw runtime_error("File not found");
		}
		catch (const exception& e) {
			cerr << "Error" << e.what() << endl;
		}
	}

	int duration, year, month, code;
	while (input >> duration >> year >> month >> code) {
		if (code == clientCode) {
			//ClientData data = { duration, year, month };
			//map_clientData[year][month] = data;
		}
	}
}

FitnessCenter::FitnessCenter(const vector<FitnessStruct>& records, int clientCode) {
	for (const auto& record : records) {
		if (record.clientCode != clientCode) {
			continue;
		}

		auto& yearData = map_data[record.year];
		yearData[record.month] += record.duration;
	}
}

void FitnessCenter::printMaxDurationByYear(ostream& out) const {
	for (const auto& yearData : map_data) {
		int year = yearData.first;
		const auto& monthData = yearData.second;
		int maxDuration = 0;
		int maxMonth = 0;

		for (const auto& monthDuration : monthData) {
			if (monthDuration.second > maxDuration) {
				maxDuration = monthDuration.second;
				maxMonth = monthDuration.first;
			}
		}

		if (maxDuration == 0) {
			out << "No data" << endl;
		}
		else {
			out << year << " " << maxMonth << " " << maxDuration << endl;
		}
	}
}