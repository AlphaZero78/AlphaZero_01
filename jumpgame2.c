#include <stdio.h>
#define MAX(a, b) ((b) > (a) ? (b) : (a))

int jump(int* nums, int numsSize) {
    int ans = 0;
    int cur_right = 0; // 已建造的桥的右端点
    int next_right = 0; // 下一座桥的右端点的最大值
    for (int i = 0; i < numsSize - 1; i++) {
        // 遍历的过程中，记录下一座桥的最远点
        next_right = MAX(next_right, i + nums[i]);
        if (i == cur_right) { // 无路可走，必须建桥
            cur_right = next_right; // 建桥后，最远可以到达 next_right
            ans++;
        }
    }
    return ans;
}

int main() {
    int numsSize;
    scanf("%d", &numsSize);
    int nums[1000];
    for (int i = 0; i < numsSize; i++) {
        scanf("%d", &nums[i]);
    }
    printf("%d\n", jump(nums, numsSize));
    return 0;
}