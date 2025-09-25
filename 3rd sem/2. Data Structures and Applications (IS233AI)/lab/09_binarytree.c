#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int val)
{
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->left = temp->right = NULL;
    temp->val = val;
    return temp;
}

void insertLeft(Node* root, int val)
{
    Node* temp = createNode(val);
    root->left = temp;
}

void insertRight(Node* root, int val)
{
    Node* temp = createNode(val);
    root->right = temp;
}

void inorder(Node* root)
{
    if (root) {
        inorder(root->left);
        printf("%d", root->val);
        inorder(root->right);
    }
}

int countNodes(Node* root)
{
    if (!root)
        return 0;
    return countNodes(root->left) + countNodes(root->right) + 1;
}

int countLeafNodes(Node* root)
{
    if (!root)
        return 0;
    if (!root->left && !root->right)
        return 1;
    return countLeafNodes(root->left) + countLeafNodes(root->right);
}

int countNonLeafNodes(Node* root)
{
    return countNodes(root) - countLeafNodes(root);
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int height(Node* root)
{
    if (!root)
        return 0;
    return max(height(root->left), height(root->right));
}

int main()
{
    Node* root = createNode(0);
    insertLeft(root, 1);
    insertRight(root, 2);
    insertRight(root->left, 3);
    insertLeft(root->right, 4);
    inorder(root);
}
