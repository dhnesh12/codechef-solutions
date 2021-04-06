#include <bits/stdc++.h>
using namespace std;
int main() {
  
     int t;
     cin>>t;
     int arr[t];
    for(int i=0;i<t;i++) cin>>arr[i];
    int ce=0;
    int co=0;
    for(int i=0;i<t;i++)
    {
        if(arr[i]%2==0) ce++;
        else co++;
        
    }
    if(co<ce) cout<<"READY FOR BATTLE";
        else cout<<"NOT READY";
    
    return 0;
}