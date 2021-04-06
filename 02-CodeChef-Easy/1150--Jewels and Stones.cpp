#include <bits/stdc++.h>
using namespace std;

int main() {
	// your code goes here
	int t;
	cin>>t;
	while(t--)
	{
	    string str1,str2;
	    cin>>str1;
	    cin>>str2;
	    sort(str1.begin(),str1.end());
	    sort(str2.begin(),str2.end());
	    int count=0;
	    for(int i=0;i<str2.length();i++)
	    {
	        for(int j=0;j<str1.length();j++)
	        {
	            if(str2[i]==str1[j])
	            {
	                count++;
	                break;
	            }
	        }
	    }
	    cout<<count<<endl;
	}
	return 0;
}