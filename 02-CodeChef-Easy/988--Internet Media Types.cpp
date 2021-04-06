#include <iostream>
#include <map>
using namespace std;

#define mp make_pair

int main() {
	// your code goes here
	int n, q;
	cin>>n>>q;
	
	map<string, string> mps;
	for(int i=0; i<n; i++)
	{
	    string s1, s2;
	    cin>>s1>>s2;
	    
	    mps.insert(mp(s1, s2));
	}
	
	/*map<string, string>::iterator itr;
	for(itr=mps.begin(); itr!=mps.end(); itr++)
	    cout<<itr->first<<" "<<itr->second<<endl;
	*/
	
	for(int i=0; i<q; i++)
	{
	    string str; cin>>str;
	    int j = str.length() - 1;
	    
	    while(j>=0 && str[j]!='.')
	    {
	        j--;
	    }
	    
	    if(j<0)
	        cout<<"unknown";
	    else
	    {
	        j++;
	        string ros = str.substr(j);
	        
	        if(mps.find(ros)!=mps.end())
	            cout<<mps[ros];
	        else
	            cout<<"unknown";
	    }
	    cout<<endl;
	}
	return 0;
}
