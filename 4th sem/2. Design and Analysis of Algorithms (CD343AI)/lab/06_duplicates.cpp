#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

bool containsDuplicates(vector<int>& arr)
{
    sort(arr.begin(), arr.end());
    for (int i = 1; i < arr.size(); i++)
        if (arr[i] == arr[i - 1])
            return 1;
    return 0;
}
