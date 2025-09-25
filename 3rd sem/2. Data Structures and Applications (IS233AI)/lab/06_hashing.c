#include <stdio.h>
#define TABLE_SIZE 10
#define PRIME 7
int hash[TABLE_SIZE];

int hash1(int key)
{
    return key % TABLE_SIZE;
}

int hash2(int key)
{
    return PRIME - (key % PRIME);
}

void initHash()
{
    for (int i = 0; i < TABLE_SIZE; i++)
        hash[i] = -1;
}

void insert(int key)
{
    int idx = hash1(key), step = hash2(key), i, new_index;
    for (i = 0; i < TABLE_SIZE; i++) {
        new_index = (idx + i * step) % TABLE_SIZE;
        if (hash[new_index] == -1) {
            hash[new_index] = key;
            return;
        }
    }
    printf("Table Full!");
}

int search(int key)
{
    int idx = hash1(key);
    int step = hash2(key);
    int i, new_index;
    for (i = 0; i < TABLE_SIZE; i++) {
        new_index = (idx + i * step) % TABLE_SIZE;
        if (hash[new_index] == -1)
            break;
        if (hash[new_index] == key)
            return new_index;
    }
    return -1;
}

void delete(int key)
{
    int i = search(key);
    if (i == -1)
        printf("Not found");
    else
        hash[i] = -1;
}

void printhash()
{
    int i;
    for (i = 0; i < TABLE_SIZE; i++)
        if (hash[i] == -1)
            printf("Empty at index %d\n", i);
        else
            printf("%d at index %d\n", hash[i], i);
}

int main()
{
    int choice, key;
    initHash();
    printf("1. Insert  2. Search  3. Delete  4. Display  5. Exit");
    while (1) {
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            printf("Enter key: ");
            scanf("%d", &key);
            insert(key);
            break;
        case 2:
            printf("Enter key: ");
            scanf("%d", &key);
            key = search(key);
            if (key == -1)
                printf("Not found");
            else
                printf("Found at %d", key);
            break;
        case 3:
            printf("Enter key: ");
            scanf("%d", &key);
            delete(key);
            break;
        case 4:
            printhash();
        }
    }
}
