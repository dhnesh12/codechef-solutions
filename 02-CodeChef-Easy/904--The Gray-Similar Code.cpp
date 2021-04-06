#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ll;

int main() {
	// your code goes here
	ll n;
	cin>>n;
	
	vector<ll> v(n);
    for(int i=0;i<n;i++){
        cin>>v[i];
    }
    
    if(n>=131){
        cout<<"Yes"<<endl;
        return 0;
    }
    
    unordered_set<ll> s;
    
    
    
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            for(int k=j+1;k<n;k++){
                for(int l=k+1;l<n;l++){
                    if((v[i]^v[j]^v[k]^v[l]) == 0){
                        cout<<"Yes"<<endl;
                        return 0;
                    }
                }
            }
            
        }
    }
    cout<<"No"<<endl;
	return 0;
}
