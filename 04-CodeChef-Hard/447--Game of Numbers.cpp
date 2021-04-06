#include<bits/stdc++.h>
using namespace std;
int gcd(int a,int b){return b?gcd(b,a%b):a;}
const int N=2e6;
int fir[N],w[N],nxt[N],to[N],cnt=1,n,a[N],b[N];
inline void add(int u,int v,int val)
{
	to[++cnt]=v,nxt[cnt]=fir[u],fir[u]=cnt,w[cnt]=val;
    to[++cnt]=u,nxt[cnt]=fir[v],fir[v]=cnt,w[cnt]=0;
}
int d[N],g[N],tcnt,s,t,c[N],tot,cr[N];
map<int,int>mp;
void bfs()
{
	queue<int>q;q.push(t);d[t]=0;g[0]=1;
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int i=fir[x];i;i=nxt[i])
		if(!~d[to[i]])d[to[i]]=d[x]+1,q.push(to[i]),g[d[to[i]]]++;
	}
}
int dfs(int x,int fl)
{
	if(x==t)return fl;int now=0;
	for(int i=cr[x];i;i=nxt[i])
	{
		if(d[to[i]]+1==d[x]&&w[i])
		{
			int y=dfs(to[i],min(fl-now,w[i]));
			w[i]-=y,w[i^1]+=y,now+=y;if(now==fl)return fl;
		}cr[x]=i;
	}if(!(--g[d[x]]))d[s]=tcnt;g[++d[x]]++,cr[x]=fir[x];return now;
}
int mian(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)scanf("%d",&b[i]);
    tcnt=2,s=1,t=2;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){
            //if(a[i]==b[j])continue;
            if(a[i]<b[j]){
                int d=gcd(a[i],b[j]);
                if(d>1){
                    int x=++tcnt;
                    for(int k=2;k*k<=d;k++){
                        if(d%k==0){int y=mp[k];if(!y)mp[k]=++tcnt,y=tcnt;add(x,y,1);}
                        while(d%k==0)d/=k;
                    }
                    if(d>1){int y=mp[d];if(!y)mp[d]=++tcnt,y=tcnt;add(x,y,1);}
                    add(s,x,1);
                }
            }
            if(a[j]>b[i]){
                int d=gcd(a[j],b[i]);
                if(d>1){
                    int x=++tcnt;
                    for(int k=2;k*k<=d;k++){
                        if(d%k==0){int y=mp[k];if(!y)mp[k]=++tcnt,y=tcnt;add(y,x,1);}
                        while(d%k==0)d/=k;
                    }
                    if(d>1){int y=mp[d];if(!y)mp[d]=++tcnt,y=tcnt;add(y,x,1);}
                    add(x,t,1);
                }
            }
        }
    for(int i=1;i<=tcnt;i++)d[i]=-1,g[i]=0,cr[i]=fir[i];
    int ans=0;bfs();while(d[s]<tcnt&&d[s]>0)ans+=dfs(s,1e9);printf("%d\n",ans);
    for(int i=1;i<=tcnt;i++)fir[i]=0;cnt=1;mp.clear();
    return 0;
}
int main(){
    int T;cin>>T;while(T--)mian();
}
