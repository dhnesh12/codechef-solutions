#include<bits/stdc++.h>
using namespace std;
#define eps 1e-9
#define dinf 1e9+1e-2
#define pb push_back
#define ll long long
typedef ll d;
struct pt
{
    d x,y;
    pt() {} pt(d x,d y):x(x),y(y) {} pt(const pt &p):x(p.x),y(p.y) {}
    pt operator + (const pt &p)const
    {
        return pt(x+p.x,y+p.y);
    }
    pt operator - (const pt &p)const
    {
        return pt(x-p.x,y-p.y);
    }
    void scan()
    {
        scanf("%lld %lld",&x,&y);
    }
    bool operator < (const pt &p)const
    {
        return ((x<p.x) || (x==p.x && y<p.y));
    }
};
d dot(pt p,pt q)
{
    return p.x*q.x+p.y*q.y;
}
d cross(pt p,pt q)
{
    return p.x*q.y-p.y*q.x;
}
d cross2(pt p,pt o,pt q)
{
    return cross(o-p,q-p);
}
d dist(pt p,pt q)
{
    return sqrtl(dot(p-q,p-q));
}
d dist2(pt p,pt q)
{
    return dot(p-q,p-q);
}
ostream &operator<<(ostream &os,const pt &p)
{
    return os << "(" << p.x << "," << p.y << ")";
}

vector<pt> convex_hull(vector<pt> vp)
{
    int n = vp.size(),k = 0;
    sort(vp.begin(),vp.end());
    if(n<=3)
    {
        if(n==3)
            if(cross2(vp[0],vp[2],vp[1])>0LL)
                swap(vp[1],vp[2]);
        return vp;
    }
    vector<pt> ret(2*n);
    for(int i=0; i<n; i++)
    {
        while(k>=2 && cross2(ret[k-2],ret[k-1],vp[i])<=0LL)
            k--;
        ret[k++] = vp[i];
    }
    for(int i = n-2,t=k+1; i>=0; i--)
    {
        while(k>=t && cross2(ret[k-2],ret[k-1],vp[i])<=0LL)
            k--;
        ret[k++] = vp[i];
    }
    ret.resize(k-1);
    return ret;
}

pt ara[50010];

vector<pt> tre[200010];

vector<pt> merg(vector<pt> &p,vector<pt> &q)
{
	vector<pt> mrg;
	for(auto x:p)mrg.pb(x); 
	for(auto x:q)mrg.pb(x);
	// sort(mrg.begin(),mrg.end());
	return convex_hull(mrg);
	// return mrg; 
}

// ll maxd2(vector<pt> &p)
// {
// 	int n = p.size();
// 	ll ret = 0LL;
// 	for(int i=0;i<n;i++)
// 		for(int j=0;j<n;j++)
// 			ret = max(ret,dist2(p[i],p[j]));
// 	return ret;
// }



ll maxd2(vector<pt> &vp)
{
	int n = vp.size();
	if(n<2) return 0;
	else if(n<=3){
		ll ret = 0;
		for(int i=0;i<n;i++)
			for(int j=i+1;j<n;j++)
				ret = max(ret,dist2(vp[i],vp[j]));
			return ret;
		}
/*ll ret = 0LL;
int i=0,j=0;
for(int i=0;i<n;i++)
{
while(dist2(vp[i],vp[(j+1)%n])>=dist2(vp[i],vp[j])) j = (j+1)%n;
ret = max(ret, dist2(vp[i],vp[j]));
}
return ret;
*/
		int i=n-1, j = 0, k = 1;
		ll ret = 0;
		while(abs(cross(vp[j]-vp[i],vp[k+1]-vp[i]))>abs(cross(vp[j]-vp[i],vp[k]-vp[i]))){
//debug(k);
			k++;
		}
//debug(k);
		i = 0, j = k;
		while(i<=k && j<n)
		{
			ret = max(dist2(vp[i],vp[j]),ret);
			while(j<n-1 &&
				abs(cross(vp[i+1]-vp[i],vp[j+1]-vp[i]))>abs(cross(vp[i+1]-vp[i],vp[j]-vp[i])))
			{
				j++;
				ret = max(dist2(vp[i],vp[j]),ret);
			}
			i++;
		}
		return ret;
	}


void build(int node,int st,int en)
{
	if(st==en)
	{
		tre[node].pb(ara[st]);
		return ;
	}
	int mid = (st+en) / 2;
	build(node*2,st,mid);
	build(node*2+1,mid+1,en);
	tre[node] = merg(tre[node*2],tre[node*2+1]);
	return;
}

vector<pt> query(int node,int st,int en,int l,int r)
{
	if(st>=l && en<=r)
	{
		return tre[node];
	}
	if(st>r || en<l)
	{
		// case handled with care 
	}
	int mid = (st+en) / 2;
	vector<pt> ret1,ret2;
	if(mid>=l)
		ret1 = query(node*2,st,mid,l,r);
	if(mid+1<=r)
		ret2 = query(node*2+1,mid+1,en,l,r);
	return merg(ret1,ret2);
}

int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		ara[i].scan();
	build(1,1,n);
	int q;
	scanf("%d",&q);
	while(q--)
	{
		int l,r;
		scanf("%d %d",&l,&r);
		vector<pt> x = query(1,1,n,l,r);
		// x = convex_hull(x);
		ll ans = maxd2(x); 
		printf("%lld\n",ans);
	}   
}