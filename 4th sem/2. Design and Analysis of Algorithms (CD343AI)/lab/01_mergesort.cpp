#include<iostream>
#include<vector>
using namespace std;

void merge(vector<int>& b, vector<int>& c, vector<int>& arr)
{
    int i{}, j{}, k{};
    while (i < b.size() && j < c.size()) 
        arr[k++] = ((b[i] < c[j]) ? b[i++] : c[j++]);
    while (i < b.size())
        arr[k++] = b[i++];
    while (j < c.size())
        arr[k++] = c[j++];
}

void mergeSort(vector<int>& arr)
{
    if (arr.size() > 1) {
        int m = arr.size() / 2;
        vector<int> b(arr.begin(), arr.begin() + m);
        vector<int> c(arr.begin() + m, arr.end());
        mergeSort(b);
        mergeSort(c);
        merge(b, c, arr);
    }
}
