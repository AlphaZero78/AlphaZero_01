#include<stdio.h>
#include"josephus.h"
int main(){
    int n,k;
    scanf("%d %d",&n,&k);
    printf("%d",ring(n,k)+1);
    return 0;
}