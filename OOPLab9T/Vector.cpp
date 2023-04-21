#include <iostream>
#include <vector>
#include <algorithm>
#include "Vector.h"

using namespace std;

void findFirstOfVector() {
    int size;
    cout << " Enter size of vector (1-100): ";
    cin >> size;

    vector<int> V(size);
    cout << " Enter " << size << " integers:" << endl;
    for (int i = 0; i < size; i++) {
        cin >> V[i];
    }

    cout << " Vector V: " << endl;
    for (int i = 0; i < size; i++) {
        cout << V[i] << " ";
    }
    cout << "\n\n";

    // Split vector on 2 parts
    vector<int>::iterator middle = V.begin() + (V.size() / 2); // 1st index + size of vec / 2
    vector<int> firstHalf(V.begin(), middle); 
    vector<int> secondHalf(middle, V.end());

    // Search 1st elem from 2nd part of vector, which mathes to elem from 1st part of vec
    vector<int>::iterator it = find_first_of(firstHalf.begin(), firstHalf.end(), secondHalf.begin(), secondHalf.end());

    // If element has been found, then add zero before it
    if (it != firstHalf.end()) {
        firstHalf.insert(it + 1, 0);
    }

    cout << " Result of find_first_of method" << endl;
    for (int i : firstHalf) {
        cout << i << " ";
    }
    for (int i : secondHalf) {
        cout << i << " ";
    }
    cout << endl;
}