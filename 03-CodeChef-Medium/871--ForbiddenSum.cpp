#include<bits/stdc++.h>
#define turn_on_clock clock_t start,end;start=clock();
#define Fox ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
#define turn_off_clock end=clock();printf("\nTime eclipse:%.5lfms\n",(double)(end-start)/CLOCKS_PER_SEC*1000);
using namespace std;
const int N=1e5;
const long long LIM=1e18;
const int INF=0x3f3f3f3f;
const double eps=1e-6;
const double PI=atan(1.0)*4;
const int mod=1e9+7;
int n,q,a[N+10];
int tot,root[N+10],lson[(N+10)<<5],rson[(N+10)<<5],sum[(N+10)<<5];
void update(int& x,int pre,int l,int r,int pos){
	x=++tot;
	lson[x]=lson[pre],rson[x]=rson[pre],sum[x]=sum[pre]+pos;
	if(l==r)return;
	int mid=(l+r)/2;
	if(pos<=mid)update(lson[x],lson[pre],l,mid,pos);
	else update(rson[x],rson[pre],mid+1,r,pos);
}
int query(int rt1,int rt2,int l,int r,int L,int R){
	if(L<=l && r<=R)return sum[rt1]-sum[rt2];
	int mid=(l+r)/2,res=0;
	if(L<=mid)res+=query(lson[rt1],lson[rt2],l,mid,L,R);
	if(R>mid)res+=query(rson[rt1],rson[rt2],mid+1,r,L,R);
	return res;
}
int main(){
	Fox;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)update(root[i],root[i-1],1,INF,a[i]);
	cin>>q;
	while(q--){
		int l,r,ans=1;cin>>l>>r;
		while(1){
			int res=query(root[r],root[l-1],1,INF,1,ans);
			if(res>=ans)ans=res+1;
			else break;
		}
		cout<<ans<<"\n";
	}
	return 0;
}
