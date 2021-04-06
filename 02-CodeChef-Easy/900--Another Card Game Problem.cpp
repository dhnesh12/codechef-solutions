#include<bits/stdc++.h>
#define REP(i,a,b) for(int i=a;i<b;i++)
using namespace std;

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
       int c,r,ansc,ansr;
       cin>>c>>r;
       
       if(c%9==0)
       ansc=c/9;
        else
        ansc=c/9 + 1;
        
        if(r%9==0)
        ansr=r/9;
        else
        ansr=r/9 + 1;
        
        if(ansc<ansr)
        cout<<"0"<<" "<<ansc<<endl;
        else
        cout<<"1"<<" "<<ansr<<endl;
        

    }
    return 0;
}