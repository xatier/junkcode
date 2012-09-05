#include <stdio.h>

int main(){
    int a,b,c,o,i,j;
    int n=0;
    while(scanf("%d %d",&i,&j)!=EOF){ 
        printf("%d %d",i,j);

        if(i>j){ 
            b=i;
            i=j;
            j=b;    
        } 
        for(a=i;a<=j;a++){

            c=a;    
            o=0; 
            while(1){
                if(c==1){
                    o++;    
                    break;  
                } 
                if(c%2==1){
                    c=c*3+1; 
                    o++; 
                } 
                else if(c%2==0){
                    c=c/2; 
                    o++; 
                }
            }

            if(o>n){
                n=o; 
            } 
        }
        printf(" %d\n",n);
        n=0; 
    } 

    return 0; 
}
/*by Xatier*/
