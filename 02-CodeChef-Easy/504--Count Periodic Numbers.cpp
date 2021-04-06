#include <bits/stdc++.h>
using namespace std;

int decToBinary(int n,int binaryNum[]){
    int i=0;
    while (n>0){
        binaryNum[i]=n%2;
        n=n/2;
        i++;
    }
    return i;
}

bool periodic(int a[],int n){
    int c=1;
    vector <int> v;
    for (int i=0;i<n;i++){
        if (a[i]==a[i+1]){
            c++;
        } else {
            v.push_back(c);
            c=1;
        }
    }
    
    if ((count(v.begin(),v.end(),v[0]))==v.size()){
        return true;
    } else {
        return false;
    }
}

int main() {
    long long t;
    cin>>t;
    while (t--){
        long long l,r;
        cin>>l>>r;
        long long ans=0;
        long long pow=2;
        
        for (int i=1;i<=31;i++){
            long long num=pow-1;
            bool e=true;
            
            while (num<=r){
                if (num>=l){
                    ans++;}
                num=num*pow;
                
                if (!e){
                    num += pow-1;
                }
                e=!e;
            }
            
            pow = pow*2;
        }
        
        cout<<ans<<endl;
    }
    
	// your code goes here
	return 0;
}
