#include <bits/stdc++.h>
using namespace std;

int main() {
	int T,ans,even,odd;
	string s;
	cin>>T;
	while(T--){
	    cin>>s;
	    ans=0;
	    even=odd=0;
	    vector<int>v(26);
	    int n=s.size();
	    for(int i=0;i<n;i++){
	        v[s[i]-'a']++;
	    }
	    for(int i=0;i<26;i++){
	        if(v[i]>1){
	            if(v[i]%2){
	                odd++;
	            }
	            even+=v[i]/2;
	        }
	        else if(v[i]==1)odd++;
	    }
	    if(!even)ans=0;
	    else if(odd>even)ans=even;
	    else{
	        ans+=odd;
	        even=even-odd;
	        even*=2;
	        ans+=even/3;
	    }
	    cout<<ans<<endl;
	}
	return 0;
}
