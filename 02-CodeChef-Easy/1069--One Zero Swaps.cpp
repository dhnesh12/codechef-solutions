#include <bits/stdc++.h>
using namespace std;

int main() {
	int T,n,cnt,flag;
	string s,p;
	cin>>T;
	while(T--){
	    cin>>n;
	    cin>>s>>p;
	    flag=1;
	    cnt=0;
	    for(int i=0;i<n;i++){
	        if(s[i]!=p[i]){
	            if(s[i]=='1')cnt++;
	            else cnt--;
	            if(cnt<0){
	                flag=0;
	                break;
	            }
	        }
	    }
	    if(flag and cnt==0)cout<<"Yes"<<endl;
	    else cout<<"No"<<endl;
	}
	return 0;
}
