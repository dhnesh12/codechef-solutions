#include <bits/stdc++.h>
using namespace std;
#define fio ios_base::sync_with_stdio(false); cin.tie(NULL)

int main() {
    fio;
	int t;
	cin>>t;
	while(t--)
	{
	    int n;
	    cin>>n;
	   // n++;
	    string r ="";
	    int i=1;
	   // cout<<n;
	   if(n==1)
	   {
	       cout<<"ba\n";
	       continue;
	   }
	    while(i<n)
	    {
	       // cout<<i<<endl;
	        char a = 'a';
	        for(int j=0;;j++)
	        {
	            if(j%26)
	            r+=(a+(j%26));
	            
	            else{
	                r+="ab";
	                j++;
	            }
	           // cout<<j<<" "<<i<<" "<<r<<endl;
	            if(i>=n) break;
	            
	            i++;
	        }
	        
	    }
	    for(int i=r.length()-1;i>=0;i--)
	    {
	        cout<<r[i];
	    }
	    cout<<endl;
	}
	return 0;
}
