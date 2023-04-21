#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <set>

using namespace std;

void findValuesWhichAbsentInAnotherVector() {
    vector<int> V1 = {1, 3, 5, 7, 9 };
    vector<int> V2 = {3, 4, 5, 5, 10, 1};

    // Creating set for storing every single element of vectors 
    multiset<int, greater<int>> M1(V1.begin(), V1.end());
    multiset<int, greater<int>> M2(V2.begin(), V2.end());

    // // Creating set for storing elements contained in one of the vectors
    multiset<int, greater<int>> result;
    set_symmetric_difference(M1.begin(), M1.end(), M2.begin(), M2.end(),
        inserter(result, result.begin()));

    set<int, greater<int>> output(result.begin(), result.end());
    for (auto num : output) {
        int count1 = M1.count(num);
        int count2 = M2.count(num);
        int maxCount = max(count1, count2);
        for (int i = 0; i < maxCount; i++) {
            cout << num << " ";
        }
    }
}

