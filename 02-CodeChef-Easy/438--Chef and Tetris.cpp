#include <iostream>
#include <cstdio>
#define gc getchar_unlocked
using namespace std;

void scanint(int &x){

    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c=gc()){
        x = (x<<1) + (x<<3) + c -48;
    }
}
bool neutralise2(int x,int &a,int &b1,int &b2){
    if(a==x)
        return true;
    if(a+b1==x)
    {
        b1=0;
        return true;
    }
    if(a+b2==x)
    {
        b2=0;
        return true;
    }
    if(a+b1+b2==x)
    {
        b1=0;
        b2=0;
        return true;
    }
    return false;
}
/*bool neutralise(int x,int &a,int &b1,int &b2,int &b3){
    if(a==x)
        return true;
    if(a+b1==x)
    {
        b1=0;
        return true;
    }
    if(a+b2==x)
    {
        b2=0;
        return true;
    }
    if(a+b3==x)
    {
        b3=0;
        return true;
    }
    if(a+b1+b2==x)
    {
        b1=0;
        b2=0;
        return true;
    }
    if(a+b1+b3==x)
    {
        b1=0;
        b3=0;
        return true;
    }
    if(a+b2+b3==x)
    {
        b2=0;
        b3=0;
        return true;
    }
    return false;
}
*/
int main()
{
    int cases;
    scanint(cases);
    while(cases--){
        int n,flag=1,max1,max2;
        max1=0;max2=0;
        long long int sum=0;
        long long int x;
        scanint(n);
        int b[n],a[n];
        for(int i=0;i<n;i++){
            scanint(b[i]);
            sum+=b[i];
            max1=max(max1,b[i]);
        }
        for(int i=0;i<n;i++){
            scanint(a[i]);
            sum+=a[i];
            max2=max(max2,a[i]);
        }
        x=sum/n;
        //printf("max1=%d  max2=%d\n",max1,max2);
        //printf("sum=%lld  x=%ld\n",sum,x);
        if(n==1){
        	printf("%lld\n",sum);
        	continue;
        }
        if((sum%n==0)&&(max1<=x)&&(max2<=x)){
			//printf("\nEntered if\n");
            if(neutralise2(x,a[0],b[0],b[1])==false){
                printf("-1\n");
                continue;
            }
            //printf("\nEntered for\n");
            for(int i=1;i<n-1;i++){

                a[i]+=b[i-1];
                if(neutralise2(x,a[i],b[i],b[i+1])==false){
                    flag=0;
                    break;
                }

            }
            if((flag!=0)&&(neutralise2(x,a[n-1],b[n-1],b[n-2]))==true){
            	//printf("\nEntered final\n");
                printf("%lld\n",x);
                continue;
            }
        }
        printf("-1\n");



    }
}
