#include<stdio.h>
#include<stdbool.h>
#define MAX(a, b) ((b) > (a) ? (b) : (a))

bool canJump(int* nums, int numsSize) {
    int mx = 0;
    for (int i = 0; i < numsSize; i++) {
        if (i > mx) { // 无法到达 i
            return false;
        }
        mx = MAX(mx, i + nums[i]); // 从 i 最右可以跳到 i + nums[i]
    }
    return true;
}
int main() {
    int nums[1000];
    int numsSize;
    scanf("%d", &numsSize);

    for (int i = 0; i < numsSize; i++) {
        scanf("%d", &nums[i]);
    }

    if (canJump(nums, numsSize)) {
        printf("Can jump to the last index.\n");
    } else {
        printf("Cannot jump to the last index.\n");
    }
    return 0;
}
