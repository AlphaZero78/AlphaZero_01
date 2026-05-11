#include <stdio.h>
#include <stdlib.h>
typedef struct BiTreeNode {
    int data;
    struct BiTreeNode* left;
    struct BiTreeNode* right;
} BiTreeNode;
BiTreeNode* createNode(int data) {
    BiTreeNode* newNode = (BiTreeNode*)malloc(sizeof(BiTreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
//层序遍历构建完全二叉树
BiTreeNode* CreateTree(FILE* fp) {
    char data;
    if ((data = fgetc(fp)) == EOF) { 
        return NULL; 
    }
    fgetc(fp);
    BiTreeNode* root = createNode(data);
    BiTreeNode* queue[100]; 
    int front = 0, rear = 0;
    queue[rear++] = root; 
    while (front < rear) {
        BiTreeNode* current = queue[front++];
        if ((data = fgetc(fp)) != EOF) {
            current->left = createNode(data);
            queue[rear++] = current->left;
            fgetc(fp);
        }
        if ((data = fgetc(fp)) != EOF) {
            current->right = createNode(data);
            queue[rear++] = current->right;
            fgetc(fp);
        }
    }
    return root;
}
//前序遍历
void PreOrder(BiTreeNode* root, FILE* fp1) {
    if (root == NULL) {
        return;
    }
    if(root->data != '#') {
        fprintf(fp1, "%c ", root->data);
    }
    PreOrder(root->left, fp1);
    PreOrder(root->right, fp1);
}
//中序遍历
void InOrder(BiTreeNode* root, FILE* fp1) {
    if (root == NULL) {
        return;
    }
    InOrder(root->left, fp1);
    if(root->data != '#') {
        fprintf(fp1, "%c ", root->data);
    }
    InOrder(root->right, fp1);
}
//后序遍历
void PostOrder(BiTreeNode* root, FILE* fp1) {
    if (root == NULL) {
        return;
    }
    PostOrder(root->left, fp1);
    PostOrder(root->right, fp1);
    if(root->data != '#') {
        fprintf(fp1, "%c ", root->data);
    }
}

int main() {
    FILE* fp = fopen("lab3_1_input.txt", "r");
    FILE* fp1=fopen("lab3_1_output.txt", "w");
    if (fp == NULL) {
        return 1;
    }
    BiTreeNode* root = CreateTree(fp);
    PreOrder(root, fp1);
    fprintf(fp1, "\n");
    InOrder(root, fp1);
    fprintf(fp1, "\n");
    PostOrder(root, fp1);
    fprintf(fp1, "\n");
    fclose(fp);
    fclose(fp1);
    return 0;
}
   