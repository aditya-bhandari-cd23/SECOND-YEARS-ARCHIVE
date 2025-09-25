// sample binary search file
#include<stdio.h>

int main()
{
    int n, key, arr[10];
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);
    printf("Enter the elements: ");
    for (int i = 0; i < n; i++)
        scanf("%d",&arr[i]);
    
    printf("Enter element to be searched: ");
    scanf("%d",&key);

    int result = 1;
    if (result == -1)
        printf("Element is not present in array");
    else
        printf("Element is present");
}