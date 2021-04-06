#include<iostream>
#include<climits>
#define ll long long int

using namespace std;

int main()
{
    int t;
    cin>>t;
    
    int n;
    while(t--){
        cin>>n;
        
        ll arr[n], min=LLONG_MAX;
        for(int i=0;i<n;i++){
            cin>>arr[i];
            if(arr[i]<min){ min=arr[i];}
        }
        
        min*=(n-1); cout<<min<<"\n";
    }
    
    return 0;
}
    