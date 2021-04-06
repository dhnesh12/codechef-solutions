#include<bits/stdc++.h>
using namespace std;
#define lf double 
#define ll long long
#define nn 525
int gr(int n) {return ((rand()*3271+rand())%n+n)%n+1;}
struct maxflow{
	vector<int> v[nn],cap[nn],rev[nn];
	void clear()
	{
		for(int i=0;i<nn;i++) v[i].clear(),cap[i].clear(),rev[i].clear();
	}
	void add_edge(int x,int y,int c)
	{
		v[x].push_back(y);cap[x].push_back(c);
		rev[x].push_back(v[y].size());
		
		v[y].push_back(x);cap[y].push_back(0);
		rev[y].push_back(v[x].size()-1);
	}	
	int dist[nn];
	void bfs(int s)
	{
		queue<int> q;q.push(s);
		memset(dist,0x3f,sizeof(dist));
		dist[s]=0;
		while(!q.empty())
		{
			int x=q.front();q.pop();
			for(int i=0;i<(int)v[x].size();i++)
			{
				if(cap[x][i])
				{
					int y=v[x][i];
					if(dist[y]>dist[x]+1)
						dist[y]=dist[x]+1,q.push(y);
				}
			}
		}
	}
	ll dfs(int x,ll lim)
	{
		if(lim==0) return 0;
		if(!dist[x]) return lim;
		int nt=0;
		for(int i=0;i<(int)v[x].size();i++)
		{
			int y=v[x][i];int j=rev[x][i];
			if(cap[y][j] and dist[y]==dist[x]-1)
			{
				ll tf=dfs(y,min(1ll*cap[y][j],lim));nt+=tf,lim-=tf;
				cap[x][i]+=tf;
				cap[y][j]-=tf;
			}
		}
		return nt;
	}
	int getflow(int s,int t)
	{
		ll res=0;
		while(1)
		{
			bfs(s);
			if(dist[t]>=1e9) break;
			res+=dfs(t,1e11);//cout<<res<<" ";
		}
		return res;
	}
}flow;



vector<int> vq[nn],vcq[nn],vd[nn],vcd[nn];
int bel[nn];int n;lf qq,dd;
struct maxanswerdatasaver{
	lf ans;int cbel[nn];
	void clear()
	{
		ans=1e11;
	}
	void upd()
	{
		if(dd)
		if(qq/dd<ans) 
		{
			ans=qq/dd;
			for(int i=1;i<=n;i++) cbel[i]=bel[i];
		}
	}
	void copy()
	{
		for(int i=1;i<=n;i++) bel[i]=cbel[i];
	}
	void output()
	{
		vector<int> vs,vt;
		for(int i=1;i<=n;i++) if(cbel[i]) vs.push_back(i);else vt.push_back(i);
		printf("%d ",(int)vs.size());for(int i=0;i<(int)vs.size();i++) printf("%d ",vs[i]);puts("");
	}
}trcyx;



void buildroad()
{
	flow.clear();
	for(int i=1;i<=n;i++) 
		for(int j=0;j<(int)vq[i].size();j++)
			flow.add_edge(i,vq[i][j],vcq[i][j]);
}
void getans()
{
	qq=dd=0;
//	bel[3]=bel[1]=bel[5]=0,bel[2]=bel[4]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<(int)vq[i].size();j++)
			if(bel[vq[i][j]]!=bel[i]) qq+=vcq[i][j];
		for(int j=0;j<(int)vd[i].size();j++)
			if(bel[vd[i][j]]!=bel[i]) dd+=vcd[i][j];
			
	}
	trcyx.upd();
//	cout<<qq<<" "<<dd<<"\n";
}
void makeans(int s,int t)
{
	flow.bfs(s);
	for(int i=1;i<=n;i++) 
		if(flow.dist[i]<1e9) 
			bel[i]=0;
		else bel[i]=1;
	getans();
}
void buildinit(lf resource)
{
	lf start=clock();
	while(clock()-start<resource*0.95)
	{
		int s=gr(n),t=gr(n);if(s==t) continue;
		buildroad();
		
		flow.getflow(s,t);
		makeans(s,t);
	}
	trcyx.copy();getans();
}

int cnt[nn];
void input()
{
	trcyx.clear();
	int dsize,qsize;cin>>n>>dsize>>qsize;
	for(int i=1;i<=n;i++) vq[i].clear(),vcq[i].clear(),vd[i].clear(),vcd[i].clear();
	
	while(dsize--)
	{
		int x,y,w;scanf("%d%d%d",&x,&y,&w);
		vd[x].push_back(y);vcd[x].push_back(w);
		vd[y].push_back(x);vcd[y].push_back(w);
	}
	
	while(qsize--)
	{
		int x,y,w;scanf("%d%d%d",&x,&y,&w);
		vq[x].push_back(y);vcq[x].push_back(w);
		vq[y].push_back(x);vcq[y].push_back(w);
	}
}


#define ratio 0.85
void solve(lf resource)
{
	input();
	buildinit(resource*0.4);
	resource*=0.6;
	lf start=clock();int dif=0;cnt[0]=cnt[1]=0;
	for(int i=1;i<=n;i++) cnt[bel[i]]++; 
//	trcyx.output();
	getans();
	while(clock()-start<resource*0.95)
	{
		int i=gr(n);assert(i>=1 and i<=n);
		ll ifq=0,ifd=0;
		if(cnt[bel[i]]==1) continue;
		cnt[bel[i]]--;
		bel[i]^=1;	
		cnt[bel[i]]++;
		for(int j=0;j<(int)vq[i].size();j++)
			if(bel[vq[i][j]]!=bel[i]) ifq+=vcq[i][j]*2;
			else ifq-=vcq[i][j]*2;
		for(int j=0;j<(int)vd[i].size();j++)
			if(bel[vd[i][j]]!=bel[i]) ifd+=vcd[i][j]*2;
			else ifd-=vcd[i][j]*2;
		
		if(dd+ifd<=1e-4) 
		{
			cnt[bel[i]]--;
			bel[i]^=1;
			cnt[bel[i]]++;
			continue;
		}
		if(dd==0 or (qq+ifq)/(dd+ifd)<qq/dd)
		{
			qq+=ifq,dd+=ifd;
			if(dif<100 and qq/dd<trcyx.ans) trcyx.upd(),dif=0;
			else if(qq/dd<trcyx.ans) trcyx.ans=qq/dd,trcyx.cbel[i]^=1;
		}
		else if(gr(1000000)>1000000*ratio)
		{
			qq+=ifq,dd+=ifd;
			dif=1;
		}
		else 
		{
			cnt[bel[i]]--;
			bel[i]^=1;
			cnt[bel[i]]++;
		}
	}
	trcyx.upd(); 
	trcyx.output();
}
int main()
{
	//freopen("a.in","r",stdin);
	srand(105);
	lf tot=0.55*CLOCKS_PER_SEC;
	int T;scanf("%d",&T);
	while(T--)
	{
		lf start=clock();
		solve(tot/(T+1)*0.95);
		tot-=clock()-start;
	}
	return 0;
}