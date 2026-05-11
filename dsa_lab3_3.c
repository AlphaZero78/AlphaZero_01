//哈夫曼树的构建与最优编码 
#include <stdio.h>
#include <stdlib.h>
typedef struct BiTreeNode {
    char data;
    int weight;
    struct BiTreeNode* left;
    struct BiTreeNode* right;
} BiTreeNode;
BiTreeNode* createNode(char data, int weight) {
    BiTreeNode* newNode = (BiTreeNode*)malloc(sizeof(BiTreeNode));
    newNode->data = data;
    newNode->weight = weight;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
int cmp(const void* a, const void* b) {
    BiTreeNode* nodeA = *(BiTreeNode**)a;
    BiTreeNode* nodeB = *(BiTreeNode**)b;
    return nodeA->weight - nodeB->weight;
}
BiTreeNode* HuffmanTree(BiTreeNode** nodes, int n) {
    while (n > 1) {
        qsort(nodes, n, sizeof(BiTreeNode*), cmp);

        BiTreeNode* left = nodes[0];
        BiTreeNode* right = nodes[1];

        BiTreeNode* newNode = createNode('#', left->weight + right->weight);
        newNode->left = left;
        newNode->right = right;

        nodes[0] = newNode;
        nodes[1] = nodes[n - 1];
        n--;
    }
    return nodes[0];
}

int main() {
    FILE* fp = fopen("lab3_3_input.txt", "r");
    FILE* fp1 = fopen("lab3_3_output.txt", "w");
    if (fp == NULL) {
        return 1;
    }
    int n;
    fscanf(fp, "%d", &n);
    BiTreeNode* treeNodes[100];
    for (int i = 0; i < n; i++) {
        char data;
        int weight;
        fscanf(fp, " %c %d", &data, &weight);
        treeNodes[i] = createNode(data, weight);
    }
    BiTreeNode* huffmanTree = HuffmanTree(treeNodes, n);
    //按照输入文件中的字符顺序，依次输出对应字符的哈夫曼编码
    for (int i = 0; i < n; i++) {
        BiTreeNode* currentNode = huffmanTree;
        char data = treeNodes[i]->data;
        char code[100];
        int index = 0;
        while (currentNode->data != data) {
            if (currentNode->left != NULL && currentNode->left->data == data) {
                code[index++] = '0';
                currentNode = currentNode->left;
            } else if (currentNode->right != NULL && currentNode->right->data == data) {
                code[index++] = '1';
                currentNode = currentNode->right;
            } else {
                break;
            }
        }
        code[index] = '\0';
        fprintf(fp1, "%c: %s\n", data, code);
    }
    fclose(fp);
    fclose(fp1);
    return 0;
}
