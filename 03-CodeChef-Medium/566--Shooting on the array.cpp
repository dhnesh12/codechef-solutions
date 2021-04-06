    #include <bits/stdc++.h>
    #define gc getchar()
    #define ll long long
    #define N 1000009
    #define root 1,1,n
    #define mid (l+r>>1)
    #define lc cur<<1
    #define rc lc|1
    #define lson lc,l,mid
    #define rson rc,mid+1,r
    #define now cur,l,r
    using namespace std;
    int n,q,a[N],Max[N<<2],Ans[N<<2];
    int read()
    {
    	int x=1;
    	char ch;
    	while (ch=gc,ch<'0'||ch>'9') if (ch=='-') x=-1;
    	int s=ch-'0';
    	while (ch=gc,ch>='0'&&ch<='9') s=s*10+ch-'0';
    	return x*s;
    }
    int calc(int cur,int l,int r,int x)
    {
    	if (l==r) return Max[cur]>x;
    	if (Max[cur]<=x) return 0;
    	if (Max[lc]<=x) return calc(rson,x);
    	else return Ans[cur]-Ans[lc]+calc(lson,x);
    }
    void ins(int cur,int l,int r,int x,int y)
    {
    	if (l==r)
    	{
    		Max[cur]+=y;
    		return;
    	}
    	if (x<=mid) ins(lson,x,y);
    	else ins(rson,x,y);
    	Ans[cur]=Ans[lc]+calc(rson,Max[lc]);
    	Max[cur]=max(Max[lc],Max[rc]);
    }
    void build(int cur,int l,int r)
    {
    	if (l==r)
    	{
    		Max[cur]=a[l];
    		Ans[cur]=1;
    		return;
    	}
    	build(lson);
    	build(rson);
    	Ans[cur]=Ans[lc]+calc(rson,Max[lc]);
    	Max[cur]=max(Max[lc],Max[rc]);
    }
    int Lim(int cur,int l,int r,int L,int R,int x)
    {
    	if (l==r)
    	{
    		if (Max[cur]>=x) return Max[cur];
    		else return 0;
    	}
    	if (L<=l&&R>=r)
    	{
    		if (Max[cur]>=x)
    		{
    			if (Max[lc]>=x) return Lim(lson,L,R,x);
    			else return Lim(rson,L,R,x);
    		}
    		else return 0;
    	}
    	if (L<=mid)
    	{
    		int tmp=Lim(lson,L,R,x);
    		if (tmp>=x) return tmp;
    	}
    	if (R>mid)
    	{
    		int tmp=Lim(rson,L,R,x);
    		if (tmp>=x) return tmp;
    	}
    	return 0;
    }
    int Ma;
    int qry(int cur,int l,int r,int L,int R)
    {
    	if (L<=l&&R>=r)
    	{
    		int tmp=calc(now,Ma);
    		Ma=max(Ma,Max[cur]);
    		return tmp;
    	}
    	int ret=0;
    	if (L<=mid) ret=qry(lson,L,R);
    	if (R>mid) ret+=qry(rson,L,R);
    	return ret;
    }
    int main()
    {
    	int T=read();
    	while (T--)
    	{
    		n=read(),q=read();
    		for (int i=1;i<=n;i++) a[i]=read();
    		build(root);
    		while (q--)
    		{
    			char ch;
    			while (ch=gc,ch!='?'&&ch!='+');
    			if (ch=='?')
    			{
    				int i=read(),l=read(),r=read();
    				int lim=Lim(root,i,n,r);
    				if (lim)
    				{
    					Ma=l-1;
    					int ans1=qry(root,i,n);
    					Ma=lim;
    					int ans2=qry(root,i,n);
    					printf("%d\n",ans1-ans2);
    				}
    				else
    				{
    					Ma=l-1;
    					int ans1=qry(root,i,n);
    					printf("%d\n",ans1);
    				}
    			}
    			else
    			{
    				int x=read(),y=read();
    				ins(root,x,y);
    			}
    		}
    	}
    	return 0;
    }
     