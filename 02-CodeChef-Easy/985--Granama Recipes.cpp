#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

int main() {
	// your code goes here
	int t; cin>>t;
	while(t--)
	{   
	    string r, s;
	    cin>>r>>s;
	    
	    string temp1 = r, temp2 = s;
	    sort(temp1.begin(), temp1.end());
	    sort(temp2.begin(), temp2.end());
	    
	    if(temp1 == temp2)
	        cout<<"YES"<<endl;

	    else
	    {
	        set<char> list1, list2;
	        for(int i=0; i<r.length(); i++)
	            list1.insert(r[i]);
	        
	        for(int i=0; i<s.length(); i++)
	            list2.insert(s[i]);
	            
	        if(list1 == list2)
	            cout<<"NO"<<endl;
	        
	        else
	            cout<<"YES"<<endl;
	    }
	}
	return 0;
}
