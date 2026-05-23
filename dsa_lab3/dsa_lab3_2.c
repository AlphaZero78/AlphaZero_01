//通过二叉树的两种遍历序列来还原其逻辑结构
#include <stdio.h>
#include <stdlib.h>
typedef struct BiTreeNode {
    int data;
    struct BiTreeNode* left;
    struct BiTreeNode* right;
} BiTreeNode;
void RestoreTree(BiTreeNode** root, char* preOrder, char* inOrder, int length) {
    if (length <= 0) {
        *root = NULL;
        return;
    }
    char rootData = preOrder[0];
    *root = (BiTreeNode*)malloc(sizeof(BiTreeNode));
    (*root)->data = rootData;
    (*root)->left = NULL;
    (*root)->right = NULL;
    int rootIndex = 0;
    for (int i = 0; i < length; i++) {
        if (inOrder[i] == rootData) {
            rootIndex = i;
            break;
        }
    }
    RestoreTree(&((*root)->left), preOrder + 1, inOrder, rootIndex);
    RestoreTree(&((*root)->right), preOrder + 1 + rootIndex, inOrder + rootIndex + 1, length - rootIndex - 1);
}
void PostOrder(BiTreeNode* root, FILE* fp1) {
    if (root == NULL) {
        return;
    }
    PostOrder(root->left, fp1);
    PostOrder(root->right, fp1);
    fprintf(fp1, "%c", root->data);
} 
int main() {
    FILE* fp = fopen("lab3_2_input.txt", "r");
    FILE* fp1 = fopen("lab3_2_output.txt", "w");
     if (fp == NULL) {
        return 1;
    }
     if (fp1 == NULL) {
        return 1;
    }
    char preOrder[100], inOrder[100];
    fgets(preOrder, 100, fp);
    fgets(inOrder, 100, fp);
    int length = 0;
    while (preOrder[length] != '\n' && preOrder[length] != '\0') {
        length++;
    }
    BiTreeNode* root = NULL;
    RestoreTree(&root, preOrder, inOrder, length);
    PostOrder(root, fp1);
    fclose(fp);
    fclose(fp1);
    return 0;
}

