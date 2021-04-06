#include <bits/stdc++.h>
using namespace std;

int main() {
	// your code goes here
	int t;
	cin>>t;
	while(t--)
	{
	    long long n;
	    cin>>n;
	    string s_one;
	    cin>>s_one;
	    long long count_z=0,count_o=0;
	    string s;
	    for(int i=0;i<n;i++)
	    {
	        cin>>s;
	        if(s[0]=='0')
	        {
	            count_z++;
	        }
	        else
	        {
	            count_o++;
	        }
	        for(int j=1;j<s.size();j++)
	        {
	            if(s[j]!=s[j-1])
	            {
	                if(s[j]=='0')
	                {
	                    count_z++;
	                }
	                else
	                {
	                    count_o++;
	                }
	            }
	            if(s[j]==s[j-1])
	            {
	                continue;
	            }
	        }
	    }
	    if(count_z==count_o)
	    {
	        cout<<s_one<<endl;
	    }
	    else
	    {
	        if(count_z>count_o)
	        {
	            cout<<"Dum"<<endl;
	        }
	        else
	        {
	            cout<<"Dee"<<endl;
	        }
	    }
	}
	return 0;
}
