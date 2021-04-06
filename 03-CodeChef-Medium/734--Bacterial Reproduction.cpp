#include <bits/stdc++.h>
using namespace std;
typedef long long int lld;
typedef vector<lld> vi;
typedef pair<lld,pair<lld,pair<lld,pair<lld,lld>>>> pi;
#define F first
#define S second
#define N 500008
#define MOD 1000000007
#define PB push_back
#define MP make_pair
#define rep(i, a, b) for (lld i = a; i < b; i++)
#define INF 100000000000000000
lld m,t,y,z,q,j,i,r,m1,m2,n,l,d,blocks,x,k,s,v;

lld a[N],vis[N],depth[N],tin[N],tout[N],timer,trees[2][8*N],ans[N];
/*0 be non leaf,1 be leaf*/
vector<lld>g[N];
// struct Query{
// 	lld type,i_minus_depth,vertex,k,time;
// 	bool operator<(const Query &other){
// 		if(other.i_minus_depth != i_minus_depth)return other.i_minus_depth > i_minus_depth;
// 		else return other.type>type;
// 	}
// };


vector<pi>queries;


void dfs(lld node=1,lld level=1){
	vis[node]++;
	tin[node]=++timer;
	depth[node]=level;
	for(auto x:g[node]){
		if(!vis[x])dfs(x,level+1);
	}
	tout[node]=timer;
}

void update(lld node,lld start,lld end,lld l,lld r,lld val,vi which){
	if(start>end||l>r||l>end||start>r)return;
	if(start>=l && end<=r){
		for(auto x:which)trees[x][node]+=val;
		return;
	}
	lld mid = (start+end)/2;
	update(2*node,start,mid,l,r,val,which);
	update(2*node+1,mid+1,end,l,r,val,which);
}

lld query(lld node,lld start,lld end,lld idx,lld which){
	if(start>end)return 0;
	if(start==end)return trees[which][node];
	lld mid = (start+end)/2;
	trees[which][2*node] += trees[which][node];
	trees[which][2*node+1] += trees[which][node];
	trees[which][node]=0;
	if(idx<=mid)return query(2*node,start,mid,idx,which);
	else return query(2*node+1,mid+1,end,idx,which);
}
bool is_leaf(lld x){return tin[x]==tout[x];}



int main(){
    
    // ios::sync_with_stdio(false);
    // cin.tie(NULL);
	// cout.tie(NULL);
scanf("%lld %lld",&n,&q);

	//fastscan(n);fastscan(q);
	rep(i,0,n-1){
	//	cin>>x>>y;
scanf("%lld %lld",&x,&y);
		// fastscan(x);fastscan(y);
		g[x].push_back(y),g[y].push_back(x);
	}
	dfs();
	rep(i,1,n+1){
		//cin>>x;
		// fastscan(x);
		scanf("%lld",&x);
//		pi qq = {0,{-1-depth[i],{i,{x,-1}}}};
		pi qq = {-1-depth[i],{0,{i+q,{i,x}}}};

		queries.push_back(qq);
		// queries.push_back({0,-1-depth[i],i,x,-1});
	}
	vi ans_queries(q,-1);
	rep(i,0,q){
		char c;
	getchar();

		//cin>>c>>v;
		scanf("%c %lld",&c,&v);
		// cout<<c<<y<<endl;
		// cin>>c;
		// fastscan(y);
		if(c=='+'){
			//cin>>k;
		//	fastscan(k);
		scanf("%lld",&k);
				pi qq = {i-depth[v],{0,{i,{v,k}}}};

		queries.push_back(qq);

		//	queries.push_back({0,i-depth[v],v,k,i});
		}
		else{
		pi qq = {i-depth[v],{1,{i,{v,-1}}}};

		queries.push_back(qq);

			// queries.push_back({1,i-depth[v],v,-1,i});
		}
	}
	sort(queries.begin(),queries.end());

	lld prev_i_minus_depth = queries[0].first;
	vector<pi>updates;
	for(int i=0;i<queries.size();i++){
		pi node = queries[i];
		//cout<<node.type<<' '<<node.vertex<<' '<<node.i_minus_depth<<endl;
		lld v = node.second.second.second.first;
		lld dept = node.first;
		lld type = node.second.first;
		lld time = node.second.second.first;
		lld k = node.second.second.second.second;
		if(prev_i_minus_depth!=dept){
			for(pi q:updates){
				update(1,1,n,tin[q.second.second.second.first],tout[q.second.second.second.first],-q.second.second.second.second,{0});
			}
			updates.clear();
		}
		if(type==0){
			update(1,1,n,tin[v],tout[v],k,{0,1});
			updates.push_back(node);
		}
		else{
			lld ans;
			if(is_leaf(v))ans=query(1,1,n,tin[v],1);
			else ans=query(1,1,n,tin[v],0);
	ans_queries[time]=ans;
			// ans_queries.push_back({node.time,ans});
		}
		prev_i_minus_depth = dept;
	}
	rep(i,0,q)if(ans_queries[i]!=-1)printf("%lld\n",ans_queries[i]);
	//for(auto x:ans_queries)printf("%lld\n",x.second);

}