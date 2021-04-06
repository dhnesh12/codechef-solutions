#include<bits/stdc++.h>
#define N 1000005
#define ll long long
#define mo 1000000007
using namespace std;
int cnt,pow2[N],T;
string s;
struct node{
	int ls,rs,tg;
	ll sz,num0,num1;
	void reset(){
		ls=rs=-1;
		num1=tg=0;
		sz=num0=1;
	}
	void updateT(int x){
		tg+=x;
		sz=(sz+2*(pow2[x]-1)*num0+(pow2[x]-1)*num1)%mo;
		sz=(sz+mo)%mo;
		num0=(num1*pow2[x-1]+num0*pow2[x])%mo;
		num1=0;
	}
};
node tr[N*2];
void pushdown(node &rt){
	if (!rt.tg) return;
	if (rt.ls==-1){
		rt.ls=cnt++;
		tr[rt.ls].reset();
		if (rt.tg>1) tr[rt.ls].updateT(rt.tg-1);
	}
	else tr[rt.ls].updateT(rt.tg);
	if (rt.rs==-1){
		rt.rs=cnt++;
		tr[rt.rs].reset();
		if (rt.tg>1) tr[rt.rs].updateT(rt.tg-1);
	}
	else tr[rt.rs].updateT(rt.tg);
	rt.tg=0;
}
void update(node &rt,int pos){
	pushdown(rt);
	if (pos+1==s.size()){
		if (s[pos]=='L') rt.ls=-1;
		else rt.rs=-1;
	}
	else{
		if (s[pos]=='L') update(tr[rt.ls],pos+1);
		else update(tr[rt.rs],pos+1);
	}
	rt.sz=1; rt.num1=rt.num0=0;
	if (rt.ls==-1) ++rt.num1;
	else{
		rt.sz+=tr[rt.ls].sz;
		rt.num0+=tr[rt.ls].num0;
		rt.num1+=tr[rt.ls].num1;
	}
	if (rt.rs==-1) ++rt.num1;
	else{
		rt.sz+=tr[rt.rs].sz;
		rt.num0+=tr[rt.rs].num0;
		rt.num1+=tr[rt.rs].num1;
	}
	if (rt.ls==-1&&rt.rs==-1)
		rt.num0=1,rt.num1=0;
	rt.sz%=mo; rt.num0%=mo; rt.num1%=mo;
}
void solve(){
	cnt=0;
	tr[cnt++].reset();
	int q,fl,x; scanf("%d",&q);
	while (q--){
		scanf("%d",&fl);
		if (fl==1){
			scanf("%d",&x);
			tr[0].updateT(x);
		}
		else{
			cin>>s;
			update(tr[0],0);
		}
		printf("%d\n",tr[0].sz);
	}
}
int main(){
	pow2[0]=1;
	for (int i=1;i<N;i++)
		pow2[i]=pow2[i-1]*2%mo;
	scanf("%d",&T);
	while (T--) solve();
}