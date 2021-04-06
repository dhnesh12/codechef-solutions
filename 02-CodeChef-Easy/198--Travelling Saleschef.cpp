#include <bits/stdc++.h>
#define pb push_back
#define endl '\n'
using namespace std;
bool go(vector<int>& temp,int cpos,int d){
	int n=temp.size();
	bool vis[n];
	memset(vis,0,sizeof(vis));
	vis[cpos]=true;
	while(cpos>=1){
		int npos=max(0,cpos-2);
		if(abs(temp[cpos]-temp[npos])>d) return false;
		cpos=npos;
		vis[cpos]=true;
	}
	for(int i=1;i<n;i++){
		if(!vis[i]){
		    if(abs(temp[i]-temp[cpos])>d) return false;
		    cpos=i;
		}
	}
	return true;
}
void reverse(vector<int>& temp){
	for(int i=0,j=temp.size()-1;i<j;i++,j--)
		swap(temp[i],temp[j]);
}
int findPos(vector<int>& temp,int v){
    for(int i=0;i<temp.size();i++){
		if(v==temp[i]) return i;
	}
	return -1;
}
int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int t,n,d,x,y;
	cin>>t;
	while(t--){
		cin>>n>>d;
		vector<int> temp;
		for(int i=0;i<n;i++) cin>>x,temp.pb(x);
		int c1=temp[0];
		sort(temp.begin(),temp.end());
		if(go(temp,findPos(temp,c1),d)){
			cout<<"YES"<<endl;
			continue;
		}
		reverse(temp);
		if(go(temp,findPos(temp,c1),d)) cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
}