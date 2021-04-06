#include <bits/stdc++.h>
#define LL long long int
#define MOD 1000000007
using namespace std;

bool prime[1000001];

void sieve(){
	memset(prime, true, sizeof prime);
	prime[0]=false;
	prime[1]=false;
	for(int i=4;i<=1000001;i+=2){
		prime[i]=false;
	}
	for(int i=3;i*i<=1000001;i+=2){
	    if(prime[i]){
		for(int j=i*i;j<=1000001;j+=i){
			prime[j]=false;
		}
	    }
	}
}


map<int,int> m[1000005];

void primeFactorise(int i){
	int count=0;
		int n=i;
		if(n%2==0){
			count=0;
			while(n%2==0){
				count++;
				n/=2;
			}
			m[i][2]=count;
		}
		for(int j=3;j*j<=n;j+=2){
			if(prime[n]){
				break;
			}
			if(n%j==0){
				count=0;
				while(n%j==0){
					n/=j;
					count++;
				}
				m[i][j]=count;
			}
		}
		if(n>1){
			m[i][n]=1;
		}

}

void printFactor(map <int, int> &ans,int i){
	for(auto it=m[i].begin();it!=m[i].end();it++){
		ans[(*it).first]+=(*it).second;
	}
}

bool printShortestPath(vector< vector<int> > &g,vector<int> &parent,int n, int u, int v){
	list<int> q;
	int f;
	vector<bool> visited(n+1, false);
	q.push_back(u);
	visited[u]=true;
	
	
	while(q.empty()==false){
		f=q.front();
		q.pop_front();
		for(auto it=g[f].begin();it!=g[f].end();it++){
			if(visited[*it]==false){
				q.push_back(*it);
				visited[*it]=true;
				parent[*it]=f;
				if(*it==v){
					return true;
				}
			}
		}
	}
	return false;
}

void solve(){
	
	int n,u,v,x,y;
	cin>>n;
	vector < vector<int> >g(n+1);
	for(int i=0;i<n-1;i++){
		cin>>x>>y;
		g[x].push_back(y);
		g[y].push_back(x);
	}

	vector<int>a(n+1);
	for(int i=1;i<=n;i++){
		cin>>a[i];
		primeFactorise(a[i]);
	}
	
	int q;
	cin>>q;
	for(int i=0;i<q;i++){
		cin>>u>>v;
		vector<int> parent(n+1,-1);
		printShortestPath(g,parent,n,u,v);
		int start=v;
		map <int, int> ans;
		while(parent[start]!=-1){
			printFactor(ans,a[start]);
			start=parent[start];
		}
		if(parent[start]==-1){
			printFactor(ans,a[start]);
		}
		LL answer=1;
		for(auto it=ans.begin();it!=ans.end();it++){
			LL factor=(LL)(*it).second;
			factor++;
			answer=(answer*factor)%MOD;
		}
		cout<<answer%MOD<<endl;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	sieve();
	int t;
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}