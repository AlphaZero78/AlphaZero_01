//元素是否互不相同
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
void cmp(int* a, int* b) {
    return (*a - *b);
}
bool isUnique(int** arr, int m,int n) {
    int* temp; // 临时数组存储所有元素
    temp = (int*)malloc(m * n * sizeof(int));
    int index = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            temp[index++] = arr[i][j];
        }
    }
    qsort(temp, m * n, sizeof(int), cmp);
    for (int i = 0; i < m * n - 1; i++) {
        if (temp[i] == temp[i + 1]) {
            free(temp);
            return false; // 找到重复元素
        }
    }
    free(temp);
    return true; // 所有元素都不同
}
