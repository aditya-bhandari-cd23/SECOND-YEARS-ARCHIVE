#include <iostream>
#include <vector>
using namespace std;

void solve(vector<int>& arr, int i, int k, vector<int>& current, vector<vector<int>>& results) {
    if (k == 0) {
        results.push_back(current);
        return;
    }
    if (i == arr.size() || k < 0)
        return;

    current.push_back(arr[i]);
    solve(arr, i + 1, k - arr[i], current, results);
    current.pop_back();
    solve(arr, i + 1, k, current, results);
}

vector<vector<int>> subsetSum(vector<int>& arr, int k)
{
    vector<vector<int>> results;
    vector<int> current;
    solve(arr, 0, k, current, results);
    return results;
}
