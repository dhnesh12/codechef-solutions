#include <bits/stdc++.h>              //Write it up on paper and follow the pattern, just write write last digits after adding. 
using namespace std;
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
        long t;
        cin>>t;
        while(t--)
        { 
            long long int n;
            cin>>n;
            long long int p=log2((long double)n);
            if(p<2)
             cout<<p<<"\n";
            else if(p%4==1)
              cout<<"9\n";
            else 
              cout<<p%4<<"\n";
        }
	return 0;
    }