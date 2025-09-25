#include <stdio.h>
#include <stdlib.h>

struct Node {
    int val;
    struct Node* left;
    struct Node* right;
};

typedef struct Node Node;

Node* createNode(int val)
{
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->val = val;
    temp->left = temp->right = NULL;
    return temp;
}

Node* insert(Node* root, int val)
{
    if (!root)
        return createNode(val);
    else if (root->val > val)
        root->left = insert(root->left, val);
    else
        root->right = insert(root->right, val);
    return root;
}

void preorder(Node* root)
{
    if (root) {
        printf("%d", root->val);
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(Node* root)
{
    if (root) {
        inorder(root->left);
        printf("%d", root->val);
        inorder(root->right);
    }
}

void postorder(Node* root)
{
    if (root) {
        postorder(root->left);
        postorder(root->right);
        printf("%d", root->val);
    }
}

Node* inorderSuccessor(Node* root)
{
    Node* temp = root;
    while (temp->left)
        temp = temp->left;
    return temp;
}

Node* delete(Node* root, int val)
{
    Node* temp;
    if (val < root->val)
        root->left = delete(root->left, val);
    if (val > root->val)
        root->right = delete(root->right, val);

    if (!root->left) {
        temp = root->right;
        free(root);
        return temp;
    }
    if (!root->right) {
        temp = root->left;
        free(root);
        return temp;
    }
    temp = inorderSuccessor(root->right);
    root->val = temp->val;
    root->right = delete(root->right, temp->val);
    return root;
}

int main()
{
    int choice, val;
    Node* root = NULL;
    printf("1. Insert  2. Delete  3. Preorder  4. Inorder  5. Postorder");
    while (1) {
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            printf("Enter element to insert: ");
            scanf("%d", &val);
            root = insert(root, val);
            break;
        case 2:
            printf("Enter element to delete: ");
            scanf("%d", &val);
            root = delete(root, val);
            break;
        case 3:
            preorder(root);
            break;
        case 4:
            inorder(root);
            break;
        case 5:
            postorder(root);
            break;
        }
    }
}
