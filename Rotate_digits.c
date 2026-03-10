//Rotate digits
#include <stdio.h>
#include <string.h>

int main() {
    char str[100];
    int n, len, i;
    
    scanf("%s", str);
    scanf("%d", &n);
    
    len = strlen(str);
    n = n % len; //m大于n,则取模
    
    // Rotate the string
    char rotated[100];
    for(i = 0; i < len; i++) {
        rotated[i] = str[(i + n) % len];
    }
    rotated[len] = '\0'; //截断字符串
    
    while(rotated[0] == '0' && len > 1) {
        // 去掉前导零
        for(i = 0; i < len - 1; i++) {
            rotated[i] = rotated[i + 1];
        }
        rotated[len - 1] = '\0';
        len--;
    }

    printf("Rotated string: %s\n", rotated);

    return 0;
}