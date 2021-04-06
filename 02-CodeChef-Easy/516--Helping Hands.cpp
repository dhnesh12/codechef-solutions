#include<bits/stdc++.h>
using namespace std;

int main() {
	// your code goes here
	bool prime[1000001];
    memset(prime, true, sizeof(prime));
 
    for (int p = 2; p * p <= 1000000; p++)
    {
        // If prime[p] is not changed, 
        // then it is a prime
        if (prime[p] == true) 
        {
            // Update all multiples 
            // of p greater than or
            // equal to the square of it
            // numbers which are multiple 
            // of p and are less than p^2 
            // are already been marked.
            for (int i = p * p; i <= 1000000; i += p)
                prime[i] = false;
        }
    }
    
    prime[1]=false,prime[0]=false;
    vector<int>prime_list(1000001,0);
    for(int i=1;i<=1000000;i++)
    {
        if(prime[i])
        prime_list[i]=prime_list[i-1]+1;
        else
        prime_list[i]=prime_list[i-1];
    }
    int t;
    cin>>t;
    int n=0;
    while(t)
    {
        
       // n++;
       // n=1000000;
       cin>>n;
        if(n==2)
        cout<<"1"<<endl;
        else if(n==1)
        cout<<"0"<<endl;
        else
        {
           int count=prime_list[n]-1;
           cout<<count+(n-2)<<endl;
        }
        t--;
    }
}
