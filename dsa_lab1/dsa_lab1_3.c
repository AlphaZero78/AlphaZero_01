//组合总和问题
#include <stdio.h>
#include <stdlib.h>
FILE *fp;
FILE *fp_output;
int RecursionCount = 0;
int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}
void FindCombination(int* num, int count, int target, int* combination, int combSize, int start,FILE* fp_output) {
    RecursionCount++;
    if (target == 0) {
        for (int i = 0; i < combSize; i++) {
            fprintf(fp_output, "%d ", combination[i]);
        }
        fprintf(fp_output, "\n");
        return;
    }
    for (int i = start; i < count; i++) {
        if (num[i] > target) {
            break;
        }
        combination[combSize] = num[i];
        FindCombination(num, count, target - num[i], combination, combSize + 1, i, fp_output);
    }
    return;
}

int main() {
    fp = fopen("lab1_3_data.txt", "r");
    fp_output = fopen("lab1_3_output.txt", "w");
    if (fp == NULL || fp_output == NULL) {
        printf("无法打开文件\n");
        return 1;
    }
    int candidates[100];
    int count = 0;
    int target;
    do{
        fscanf(fp, "%d", &candidates[count]);
        count++;
    } while (fgetc(fp) != '\n');
    fscanf(fp, "%d", &target);
    qsort(candidates, count, sizeof(int), cmp);
    int combination[100];
    FindCombination(candidates, count, target, combination, 0, 0, fp_output);
    fprintf(fp_output, "%d\n", RecursionCount);

    fclose(fp);
    fclose(fp_output);
    return 0;
}