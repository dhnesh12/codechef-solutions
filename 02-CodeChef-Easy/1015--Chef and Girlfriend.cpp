#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fast cin.tie(0);ios_base::sync_with_stdio(0);cin.tie(NULL);
#define w(t) long long int t;cin>>t;while(t--)
#define f for(ll i=0;i<n;i++)

int main(){
    w(t){
        string s1,s2;
        int d;
        cin>>s1>>s2>>d;
        int m1=((s1[0]-'0')*10+(s1[1]-'0'))*60+((s1[3]-'0')*10+(s1[4]-'0'));
        int m2=((s2[0]-'0')*10+(s2[1]-'0'))*60+((s2[3]-'0')*10+(s2[4]-'0'));
        
        float t1=(float)((m1-m2)+d);
        float t2;
        if(2*d<(m1-m2))
            t2=(float)((m1-m2));
        else
            t2=((m1-m2)/2.0+(d));
        cout<<setprecision(1)<<fixed<<t1<<" "<<setprecision(1)<<fixed<<t2<<"\n";
    }
}

  
  

