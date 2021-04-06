#include<iostream>
#include<math.h>
using namespace std;

int square(int);
int main()
{
    int t;
    cin>>t;
    while (t--)
    {
        int n;
        cin>>n;
        cout<<square(n)<<endl;
    }
    
}
int square(int a){
    int i,j=0,k;
    while(a!=0){
        i=pow(a,0.5);
        j++;
        a=a-i*i;
        square(a);
    }
    return j;
}