#include <bits/stdc++.h>
#define REP(i,a,n) for(int i=a;i<n;i++)
#define pb push_back
#define ll long long int
#define endl '\n'
using namespace std;
int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int t,n,x,y;
	cin>>t;
	while(t--){
		cin>>n;
		vector<int> graph[n+1];
		REP(i,1,n){
			cin>>x>>y;
			graph[x].pb(y);graph[y].pb(x);
		}
		int depth[n+1],turn=0;
		memset(depth,-1,sizeof(depth));
		depth[1]=0;
		queue<int> q;
		deque<int> dq;
		q.push(1);
		while(!q.empty()){
			int front=q.front();q.pop();
			dq.pb(front);
			for(int i:graph[front]){
				if(depth[i]==-1){
					depth[i]=depth[front]+1;
					q.push(i);
				}
			}
		}
		while(!dq.empty()){
			if((turn&1)) dq.pop_back();
			else{
				int front=dq.front();
				while(!dq.empty() && depth[front]==depth[dq.front()]) dq.pop_front();
			} 
			turn++;
		}
		cout<<turn<<endl;
	}
}