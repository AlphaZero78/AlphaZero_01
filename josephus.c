#include<stdio.h>
int ring(int n, int k){
    if(n==1){
        return 0;
    }
    else{
        return (ring(n-1,k)+k)%n;
    }
}
int main(){
    int n,k;
    scanf("%d %d",&n,&k);
    printf("%d",ring(n,k)+1);
    return 0;
}