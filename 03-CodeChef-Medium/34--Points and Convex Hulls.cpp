#include<bits/stdc++.h>
#define ll long long
#define uint unsigned
#define ull unsigned ll
#define pii pair<int,int>
#define pll pair<ll,ll>
#define PB push_back
#define fi first
#define se second
#define For(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define Rep(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
#define CLR(a,v) memset(a,v,sizeof(a))
#define CPY(a,b) memcpy(a,b,sizeof(a))
using namespace std;
const int N=305;
const int mo=1000000007;
struct P{
	ll x,y;
	P(){}
	P(ll _x,ll _y){x=_x,y=_y;}
	P operator +(const P &a)const{
		return P(x+a.x,y+a.y);
	}
	P operator -(const P &a)const{
		return P(x-a.x,y-a.y);
	}
	ll operator *(const P &a)const{
		return x*a.y-y*a.x;
	}
}p[N],ori;
ll check(P x,P y,P z){
	return (y-x)*(z-x);
}
int check(P a,P b,P c,P x){
	if (check(a,b,x)>0&&check(b,c,x)>0&&check(c,a,x)>0) return 1;
	if (check(a,b,x)<0&&check(b,c,x)<0&&check(c,a,x)<0) return -1;
	return 0;
}
struct node{
	P p;
	int val,id;
	bool operator <(const node &a)const{
		return check(ori,p,a.p)>0;
	}
};
vector<node> le,ri;
int s[N][N],s1[N],s2[N];
int n,ans,Pw[N];
void solve(P p,int *s){
	ori=p;
	sort(le.begin(),le.end());
	sort(ri.begin(),ri.end());
	int pos=0,sum=0;
	For(i,0,ri.size()-1){
		for (;pos<le.size()&&check(ori,ri[i].p,le[pos].p)>0;++pos)
			sum=(sum+le[pos].val)%mo;
		s[ri[i].id]=sum;
	}
}
int main(){
	Pw[0]=1;
	For(i,1,N-1) Pw[i]=Pw[i-1]*2%mo;
	scanf("%d",&n);
	For(i,1,n) scanf("%lld%lld",&p[i].x,&p[i].y);
	For(i,1,n) For(j,1,n) For(k,1,n)
		s[i][j]+=check(p[1],p[i],p[j],p[k]);
	int ans=0;
	For(i,1,n) For(j,i+1,n){
		le.clear(); ri.clear();
		For(k,1,n) if (j!=k&&i!=k){
			int cnt=s[i][j]+s[j][k]+s[k][i];
			cnt-=check(p[1],p[i],p[j],p[k]);
			cnt-=check(p[1],p[j],p[k],p[i]);
			cnt-=check(p[1],p[k],p[i],p[j]);
			cnt+=check(p[i],p[j],p[k],p[1]);
			if (cnt<0) cnt*=-1;
			if (check(p[i],p[j],p[k])>0)
				le.PB((node){p[k],Pw[cnt],k});
			else ri.PB((node){p[k],Pw[cnt],k});
		}
		solve(p[i],s1);
		solve(p[j],s2);
		For(k,0,ri.size()-1){
			int id=ri[k].id;
			ans=(ans+1ll*(s1[id]-s2[id]+mo)*ri[k].val)%mo;
		}
	}
	ans=1ll*ans*(mo+1)/2%mo;
	printf("%d\n",ans);
}