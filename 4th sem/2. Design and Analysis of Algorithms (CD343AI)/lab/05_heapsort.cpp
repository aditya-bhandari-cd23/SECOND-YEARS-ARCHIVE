#include<iostream>
#include<vector>
using namespace std;

void heapify(vector<int>& arr, int i, int n)
{
    int l = i*2 + 1;
    int r = i*2 + 2;
    int maxi = i;

    if (l < n && arr[l] > arr[maxi])
        maxi = l;
    if (r < n && arr[r] > arr[maxi])
        maxi = r;

    if (maxi != i) {
        swap(arr[maxi], arr[i]);
        heapify(arr, maxi, n);
    }
}

void heapSort(vector<int>& arr)
{
    for (int i = arr.size() / 2 - 1; i >= 0; i--) 
        heapify(arr, i, arr.size());

    for (int i = arr.size() - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, 0, i);
    }
}
