#include<stdio.h>
#include<math.h>
double fac(int n){
    double s=1;
    for(int i=1;i<=n;i++){
        s*=i;
    }
    return s;
}
double e(double x){
    double sum=1.0;
    for(int i=1;i<=19;i++){
        double q=fac(i);
        double p=pow(x,i);
        sum+=p/q;
    }
    return sum;
}
int main(){
    double x;
    scanf("%lf",&x);
    printf("%lf",e(x));
    return 0;
}