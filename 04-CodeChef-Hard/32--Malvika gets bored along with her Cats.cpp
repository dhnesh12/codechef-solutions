#include <bits/stdc++.h>
//#include <bits/stdc.h>
#define finc(i,a,b) for(int i=a; i<=b; ++i)
#define fdec(i,a,b) for(int i=a; i>=b; --i)
using namespace std;

const int
    max_N = 100003;
int
    n, A[max_N], P[max_N], BitL[max_N], PL[max_N], BitR[max_N], PR[max_N], ID[max_N], Tree[4*max_N];

void updateL(int u, int x){
    while (u>=1) BitL[u]=min(BitL[u],x), u-=u&-u;
}
int getL(int u){
    int rr=n+1;
    while (u<=n) rr=min(rr,BitL[u]), u+=u&-u;
    return rr;
}
void initL(int u){
    while (u>=1) BitL[u]=n+1, u-=u&-u;
}

void updateR(int u, int x){
    while (u<=n) BitR[u]=max(BitR[u],x), u+=u&-u;
}
int getR(int u){
    int rr=0;
    while (u>=1) rr=max(rr,BitR[u]), u-=u&-u;
    return rr;
}
void initR(int u){
    while (u<=n) BitR[u]=0, u+=u&-u;
}

void update(int id, int l, int r, int u, int val){
    if (l==r) {Tree[id]=val; return;}
    int mid=(l+r)/2;
    if (u>mid) update(id*2+1,mid+1,r,u,val);
          else update(id*2,l,mid,u,val);
    Tree[id]=min(Tree[2*id],Tree[2*id+1]);
}
int get(int id, int l, int r, int u, int v){
    if (u>v||l>v||r<u) return n;
    if (u<=l&&r<=v) return Tree[id];
    int mid=(l+r)/2;
    return min(get(id*2,l,mid,u,v),get(id*2+1,mid+1,r,u,v));
}
void build(int id, int l, int r){
    if (l==r) {if (P[l]==n) P[l]=1; else ++P[l]; return;}
    int mid=(l+r)/2;
    build(id*2,l,mid);

    fdec(i,mid,l) PL[i]=getL(A[i]+1), updateL(A[i],A[i]);
    fdec(i,mid,l) initL(A[i]);
    finc(i,mid+1,r) PR[i]=getR(A[i]-1), updateR(A[i],A[i]);
    finc(i,mid+1,r) initR(A[i]);

    finc(i,l,r) ID[i]=i;
    sort(ID+l,ID+mid+1,[](int i, int j){return PL[i]<PL[j];});
    sort(ID+mid+1,ID+r+1,[](int i, int j){return A[i]<A[j];});
    int tmp=mid;
    fdec(i,r,mid+1){
        while (tmp>=l&&PL[ID[tmp]]>A[ID[i]]) update(1,1,n,A[ID[tmp]],P[ID[tmp]]), --tmp;
        P[ID[i]]=min(P[ID[i]],get(1,1,n,PR[ID[i]]+1,A[ID[i]]-1));
    }
    finc(i,l,mid) update(1,1,n,A[i],n);
    build(id*2+1,mid+1,r);
}

void solve(){
    ++n; A[n]=n;
    finc(i,1,4*n) Tree[i]=n;
    finc(i,1,n) BitL[i]=n+1, BitR[i]=0, P[i]=n;
    build(1,1,n);
    cout << P[n]-1 << endl;
}

int main(){
 //   freopen("chn04.inp","r",stdin);
//    freopen("chn04.out","w",stdout);
    int t;
	cin >> t;
	while(t--){
		cin >> n;
		finc(i,1,n) cin >> A[i];
		solve();
	}
}

