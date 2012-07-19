#include <stdio.h>
int f(int n){
    int i,t=1;
    for(i=n;i>0;i--)t=t*i;
    return t;
}
int c(int n,int k){
    int t;
    t=f(n)/(f(k)*f(n-k));
    return t;
}
int main(void){
    int n, k;
    printf("Enter c(n,k), n>=k>=0:");
    while(scanf("c ( %d , %d )",&n,&k)!=EOF){
        getchar();
        printf("c(%d,%d) = %d!/(%d!%d!) = %d/(%d*%d) = %d\n",n,k,n,k,n-k,f(n),f(k),f(n-k),c(n,k));
        printf("Enter c(n,k), n>=k>=0:");
    }
}
