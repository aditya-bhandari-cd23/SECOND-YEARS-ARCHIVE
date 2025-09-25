#include<iostream>
#include<vector>
using namespace std;

int partition(vector<int>& arr, int low, int high)
{
    int i = low + 1, j = high, piv = arr[low];

    while (i <= j) {
        while (i <= high && arr[i] < arr[low])
            i++;
        while (j >= low && arr[j] > arr[low])
            j--;
        if (i < j)
            swap(arr[i++], arr[j--]);
    }
    swap(arr[low], arr[j]);
    return j;
}

void quickSort(vector<int>& arr, int l, int r)
{
    if (l < r) {
        int piv = partition(arr, l, r);
        quickSort(arr, l, piv - 1);
        quickSort(arr, piv + 1, r);
    }
}
