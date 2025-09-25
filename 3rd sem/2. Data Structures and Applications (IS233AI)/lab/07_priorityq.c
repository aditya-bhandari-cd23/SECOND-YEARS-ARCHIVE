#include <stdio.h>
#define SIZE 20

void heapify(int arr[], int n)
{
    int i, v, k, j;
    for (i = n / 2; i > 0; i--) {
        k = i;
        v = arr[k];
        while (k * 2 <= n) {
            j = k * 2;
            if (j < n && arr[j] < arr[j + 1])
                j++;
            if (v < arr[j]) {
                arr[k] = arr[j];
                k = j;
            }
            else
                break;
        }
        arr[k] = v;
    }
}

int main7()
{
    int choice, n, i, arr[SIZE];
    printf("1. Createheap  2. Extractmax  3. Exit");
    while (1) {
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            printf("Enter no of elements: ");
            scanf("%d", &n);
            for (i = 1; i <= n; i++)
                scanf("%d", &arr[i]);
            heapify(arr, n);
            printf("After heapify:\n");
            for (i = 1; i <= n; i++)
                printf("%d ", arr[i]);
            break;
        case 2:
            if (n > 1) {
                printf("Max: %d", arr[1]);
                arr[1] = arr[n--];
                heapify(arr, n);
            }
            else
                printf("Empty!");
            break;
        case 3:
            return 0;
        }
    }
}
