#include <bits/stdc++.h>
#define fi first
#define se second

using namespace std;

typedef long long lint;
typedef pair<int,int> ii;
const int MAXN = 1e5+222;

struct node{ int l,r,x,y,loc; } qu[MAXN];

int N,M,ar[MAXN];
lint fen1[MAXN],fen2[MAXN];
priority_queue< ii,vector<ii>,greater<ii> > q;

bool comp(const node &a,const node &b){
	return a.l<b.l;
}

void upd(lint *f,int a1,lint p){
	for(int i=a1;i<=M;i+=i&-i)
		f[i]+=p;
}

lint find(lint *f,int a1){
	lint ret=0;
	for(int i=a1;i;i-=i&-i)
		ret+=f[i];
	return ret;
}

int main(){

	scanf(" %d",&N);
	for(int i=1;i<=N;i++)
		scanf(" %d",&ar[i]);
	for(int i=1,a;i<=N;i++){
		scanf(" %d",&a);
		ar[i]=a-ar[i];
	}
	scanf(" %d",&M);
	for(int i=1;i<=M;i++)
		scanf(" %d %d %d %d",&qu[i].l,&qu[i].r,&qu[i].x,&qu[i].y),qu[i].loc=i;

	sort(qu+1,qu+M+1,comp);

	for(int i=1,j=1;i<=N;i++){
		while(j<=M && qu[j].l<=i){
			upd(fen1,qu[j].loc,qu[j].x-1ll*qu[j].l*qu[j].y);
			upd(fen2,qu[j].loc,qu[j].y);
			q.push(ii(qu[j].r,j));
			j++;
		}
		while(!q.empty() && q.top().fi<i){
			int a=q.top().se;
			upd(fen1,qu[a].loc,1ll*qu[a].l*qu[a].y-qu[a].x);
			upd(fen2,qu[a].loc,-qu[a].y);
			q.pop();
		}
		int cur=0;
		for(int step=16;step>=0;step--){
			if(cur+(1<<step)>M) continue;
			if(find(fen1,cur+(1<<step))+find(fen2,cur+(1<<step))*i<ar[i])
				cur+=(1<<step);
		}
		cur++;
		if(ar[i]<=0) cur=0;
		if(cur==M+1) cur=-1;
		printf("%d ",cur);
	}
	printf("\n");

	return 0;
}
