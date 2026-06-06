//二叉查找树BST的动态维护与验证
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct TreeNode {
    int key;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;
bool Search(TreeNode* root, int key) {
    if (root == NULL) return false;
    if (key == root->key) return true;
    else if (key < root->key) return Search(root->left, key);
    else return Search(root->right, key);
}
TreeNode* Insert(TreeNode* root, int key) {
    if (root == NULL) {
        TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
        newNode->key = key;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    if (key < root->key) root->left = Insert(root->left, key);
    else if (key > root->key) root->right = Insert(root->right, key);
    return root;
}
TreeNode* Delete(TreeNode* root, int key) {
    if (root == NULL) return NULL;
    if (key < root->key) root->left = Delete(root->left, key);
    else if (key > root->key) root->right = Delete(root->right, key);
    else {
        if(!root->left && !root->right) {
            free(root);
            return NULL;
        }
        else if(!root->left) {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        }
        else if(!root->right) {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        }
        else {
            TreeNode* temp = root->left;
            while (temp->right != NULL) temp = temp->right;
            root->key = temp->key;
            Delete(root->left, temp->key);
        }
    }
    return root;
}
void Preorder(TreeNode* root, FILE* fp_out) {
    if (root != NULL) {
        fprintf(fp_out, "%d ", root->key);
        Preorder(root->left, fp_out);
        Preorder(root->right, fp_out);
    }
}
void Inorder(TreeNode* root, FILE* fp_out) {
    if (root != NULL) {
        Inorder(root->left, fp_out);
        fprintf(fp_out, "%d ", root->key);
        Inorder(root->right, fp_out);
    }
}
int main(){
    FILE* fp = fopen("lab5_2_data.txt", "r");
    FILE* fp_out = fopen("lab5_2_output.txt", "w");
    if (fp == NULL || fp_out == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    TreeNode* root = NULL;
    int key,key_delete;
    char ch = ' ';
    while (ch != '\n') {
        int num;
        fscanf(fp, "%d", &num);
        root = Insert(root, num);
        ch = fgetc(fp);
    }

    fscanf(fp, "%d", &key);
    fscanf(fp, "%d", &key_delete);

    if(Search(root, key)) {
        fprintf(fp_out, "true\n");
    } else {
        fprintf(fp_out, "inserted\n");
        Insert(root, key);
    }
    if(Search(root, key_delete)) {
        fprintf(fp_out, "deleted\n");
        Delete(root, key_delete);
    } else {
        fprintf(fp_out, "not found\n");
    }
    
    Preorder(root, fp_out);
    fprintf(fp_out, "\n");
    Inorder(root, fp_out);

    fclose(fp);
    fclose(fp_out);
    return 0;
}