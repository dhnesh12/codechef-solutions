#include <bits/stdc++.h>
using namespace std;
#pragma optimize("-O3")
#define int long long int
#define f first
#define s second
#define pb push_back
#define endl '\n'

 
 
main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int t;
	cin>>t;
	while(t--){
		string st;
		cin>>st;
		int rem=0;
		for(int i=0; i<st.size(); i++){
			if(st[i]=='R'){
				rem=(rem*2+1)%3;
			}
			else{
				rem=(rem*2)%3;
			}
		}
		if(rem==0){
			cout<<"Animesh"<<endl;
		}
		else{
			cout<<"Malvika"<<endl;
		}
	}
	return 0;
}
