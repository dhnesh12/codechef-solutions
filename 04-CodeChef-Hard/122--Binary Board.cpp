#include<bits/stdc++.h>
using namespace std;
#define N 1000010
#define int long long
int T;
int h[N],nxt[N],v[N],w[N],s,t,dep[N],ec,ans,v1[N],v2[N],inf=1e10,n,m,id[510][510],st[N],tp;
char c[1000][1000];
void add(int x,int y,int z){
	v[++ec]=y;
	w[ec]=z;
	nxt[ec]=h[x];
	h[x]=ec;
}
void adj(int x,int y,int z){
	add(x,y,z);
	add(y,x,0);
}
bool bfs(){
    queue<int>q;
	q.push(s);
    for(int i=1;i<=ec;i++)
    	dep[i]=0;
	dep[s]=1;
    while(!q.empty()){
        int x=q.front();q.pop();
        for(int i=h[x];i;i=nxt[i])
            if(w[i]&&!dep[v[i]]){
            	dep[v[i]]=dep[x]+1;
				q.push(v[i]);
            	if(v[i]==t)
					return 1;
			}
    }
	return 0;
}
int dfs(int x,int dis){
    if(x==t)return dis;
	int tp=dis;
    for(int i=h[x];i;i=nxt[i])
        if(dep[v[i]]==dep[x]+1&&w[i]){
            int f=dfs(v[i],min(tp,w[i]));
            if(!f)
				dep[v[i]]=0;
            tp-=f;
            w[i]-=f;
			w[i^1]+=f;
            if(!tp)
				break;
        }
    return dis-tp;
}
int din(){
    int aans=0;
    while(bfs()){
    	int v;
    	while(v=dfs(s,inf))
			aans+=v;
	}
    return aans;
}
signed main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld%lld",&n,&m);
		ec=1;
		ans=0;
		memset(h,0,sizeof(h));
		for(int i=1;i<=n;i++)
			scanf("%s",c[i]+1);
		for(int i=1;i<=min(n,m);i++)
			scanf("%lld",&v1[i]);
		for(int i=1;i<=min(n,m);i++)
			scanf("%lld",&v2[i]);
		s=1;
		t=2;
		int cc=2;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				if(c[i][j]=='?')
					id[i][j]=++cc;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				for(int k=1;k<=min(i,j);k++){
					int d[3]={0,0,0};
					tp=0;
					for(int a=i-k+1;a<=i;a++)
						for(int b=j-k+1;b<=j;b++){
							if(c[a][b]=='?'){
								d[2]++;
								st[++tp]=id[a][b];
							}
							if(c[a][b]=='0')
								d[0]++;
							if(c[a][b]=='1')
								d[1]++;
						}
					if(!tp){
						if(d[0]==k*k)
							ans+=v1[k];
						if(d[1]==k*k)
							ans+=v2[k];
					}
					else{
						if(d[0]+d[2]==k*k){
							cc++;
							ans+=v1[k];
							for(int l=1;l<=tp;l++)
								adj(cc,st[l],inf);
							adj(s,cc,v1[k]);
						}
						if(d[1]+d[2]==k*k){
							cc++;
							ans+=v2[k];
							for(int l=1;l<=tp;l++)
								adj(st[l],cc,inf);
							adj(cc,t,v2[k]);
						}
					}
				}
		printf("%lld\n",ans-din());
	}
}