//哈夫曼树的构建与最优编码 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
void BuildCodes(BiTreeNode* root, char codes[256][101], char code[101], int depth) {
    if (root == NULL) {
        return;
    }
    if (root->left == NULL && root->right == NULL) {
        if (depth == 0) {
            code[depth++] = '0';
        }
        code[depth] = '\0';
        strcpy(codes[(unsigned char)root->data], code);
        return;
    }
    code[depth] = '0';
    BuildCodes(root->left, codes, code, depth + 1);
    code[depth] = '1';
    BuildCodes(root->right, codes, code, depth + 1);
}

int main() {
    int n;
    FILE* fp = fopen("lab3_3_input.txt", "r");
    if (fp == NULL) {
        return 1;
    }
    fscanf(fp, "%d", &n);
    FILE* fp1 = fopen("lab3_3_output.txt", "w");
    if (fp1 == NULL) {
        fclose(fp);
        return 1;
    }
    BiTreeNode* treeNodes[100];
    char chars[100];
    for (int i = 0; i < n; i++) {
        char data;
        int weight;
        fscanf(fp, " %c %d", &data, &weight);
        chars[i] = data;
        treeNodes[i] = createNode(data, weight);
    }
    // 按照输入文件中的字符顺序，依次输出对应字符的哈夫曼编码

    BiTreeNode* root = HuffmanTree(treeNodes, n);
    char codes[256][101] = {0};
    char code[101];
    BuildCodes(root, codes, code, 0);

    for (int i = 0; i < n; i++) {
        fprintf(fp1, "%c %s\n", chars[i], codes[(unsigned char)chars[i]]);
    }

    fclose(fp);
    fclose(fp1);
    return 0;
}
