using namespace std;
#include <bits/stdc++.h>
#include<iterator>
#include<map>
#define fast ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define ll long long int

int main()
{
	// your code goes here
	fast;
	int t;
	string str;
	
	cin>>t;
	while(t--)
	{
	    cin>>str;
	    bool flag = 0;
	    
	    for(int i=0;i<str.size()-1;i++)
	    {
	        if(str.substr(i, 3) == "101" || str.substr(i, 3) == "010")
	        {
	            flag = 1;
	            break;
	        }
	    }
	    
	    if(flag)
	        cout<<"Good\n";
        
        else
            cout<<"Bad\n";
	}
	
    return 0;
}
