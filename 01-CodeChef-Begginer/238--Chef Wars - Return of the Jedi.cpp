#include<iostream>
#include<cmath>
using namespace std;
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int a,b;
        scanf("%d %d",&a,&b);
        int rem=a;
        while(b>0 && rem>0){
            rem  = rem - b;
            b = floor(b/2);
        }
        if(rem>0){
            printf("0\n");
        }
        else{
            printf("1\n");
        }




    }




}
