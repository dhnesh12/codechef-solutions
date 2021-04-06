#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<queue>
#include<set>
#include<map>
#include<stack>
#include<bitset>

#define pb push_back
#define mp make_pair

using namespace std;

typedef unsigned int u32;
typedef long long LL;
typedef unsigned long long ULL;
typedef long double lod;
typedef pair<int,int> PR;
typedef vector<int> VI;

const lod pi=acos(-1);
const int oo=1<<30;
const LL OO=1e18;

const int N=1e5;

int gi() {
	int w=0;bool q=1;char c=getchar();
	while ((c<'0'||c>'9') && c!='-') c=getchar();
	if (c=='-') q=0,c=getchar();
	while (c>='0'&&c <= '9') w=w*10+c-'0',c=getchar();
	return q? w:-w;
}

int fa[N],siz[N];
inline int find(int x) { return fa[x]==x?x:fa[x]=find(fa[x]); }

int main()
{
#ifndef ONLINE_JUDGE
	freopen("Two_Magicians.in","r",stdin);
	freopen("Two_Magicians.out","w",stdout);
#endif
	int T=gi(),n,m,p,a,b,i,one,two;LL e;
	while (T--) {
		n=gi(),m=gi(),p=gi();
		for (i=1;i<=n;i++) fa[i]=i,siz[i]=1;
		e=1LL*n*(n-1)/2-m;
		while (m--)
			if ((a=find(gi()))^(b=find(gi())))
				siz[a]^=siz[b],fa[b]=a;
		if (find(1)==find(2)) puts("First");
		else {
			for (i=1,one=two=0;i<=n;i++) if (fa[i]==i) siz[i]&1?one++:two++;
			if (n&1) puts(e&1?"First":"Second");
			else if (!p) puts((e&1?!siz[fa[1]]||!siz[fa[2]]:siz[fa[1]]||siz[fa[2]])?"First":"Second");
			else puts((e&1?two||one>2:one==2&&two<=1)?"First":"Second");
		}
	}
	return 0;
}
