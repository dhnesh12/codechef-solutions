#include <bits/stdc++.h>

#define ll          long long
#define pb          push_back
#define pii         pair<int,int>
#define vi          vector<int>
#define vii         vector<pii>
#define mi          map<int,int>
#define mii         map<pii,int>
#define all(a)      (a).begin(),(a).end()
#define x           first
#define y           second
#define sz(x)       (int)x.size()
#define endl        '\n'
#define hell        1000000007
#define rep(i,a,b)  for(int i=a;i<b;i++)
using namespace std;
#define MAXN        100005
pair<pii,int> suf[MAXN];
int sa[MAXN],inv[MAXN],lcp[MAXN];
void radixyort(int n){
    vi cnt(n+1);
    vector<pair<pii,int>> tmp(n);
    int i;
    for(i=0;i<n;i++)cnt[suf[i].x.y]++;
    for(i=1;i<=n;i++)cnt[i]+=cnt[i-1];
    for(i=n-1;i>=0;i--)tmp[--cnt[suf[i].x.y]]=suf[i];
    fill(all(cnt),0);
    for(i=0;i<n;i++)cnt[suf[i].x.x]++;
    for(i=1;i<=n;i++)cnt[i]+=cnt[i-1];
    for(i=n-1;i>=0;i--)suf[--cnt[tmp[i].x.x]]=tmp[i];
}
void buildyA(string& s){
    int i,l;
    for(i=0;i<sz(s);i++)
        suf[i]={{s[i],(i+1<sz(s))?s[i+1]:0},i};
    sort(suf,suf+sz(s));
    for(i=0;i<sz(s);i++)inv[suf[i].y]=i;
    sa[0]=1;
    for(l=4;l<2*sz(s);l*=2){
        for(i=1;i<sz(s);i++)
            sa[i]=sa[i-1]+(suf[i].x>suf[i-1].x);
        for(i=0;i<sz(s);i++)
        	suf[i].x={sa[i],(suf[i].y+l/2<sz(s))?sa[inv[suf[i].y+l/2]]:0};
        radixyort(sz(s));
        for(i=0;i<sz(s);i++)inv[suf[i].y]=i;
    }
    for(i=0;i<sz(s);i++)sa[i]=suf[i].y;
}
void kasai(string& s){
    int i,j,k;
    for(i=k=0;i<sz(s);i++,k=max(0,k-1)){
        if(inv[i]==sz(s)-1)
        	k=0;
        else
        	for(j=sa[inv[i]+1];i+k<sz(s) and j+k<sz(s) and s[i+k]==s[j+k];k++);
        lcp[inv[i]]=k;
    }
}
string s;
int q;
int splcp[100005][20];
int spsa[100005][20];
void sparse(){
	rep(i,0,20){
		rep(j,0,sz(s)){
			if(i==0) splcp[j][i]=lcp[j],spsa[j][i]=sa[j];
			else{
				splcp[j][i]=min(splcp[j][i-1],splcp[min(j+(1<<(i-1)),sz(s)-2)][i-1]);
				spsa[j][i]=min(spsa[j][i-1],spsa[min(j+(1<<(i-1)),sz(s)-1)][i-1]);
			}
		}
	}
}
int query_lcp(int l,int r){
	if(l>r) return hell;
	int del=log2(r-l+1);
	return min(splcp[l][del],splcp[r-(1<<del)+1][del]);
}
int query_sa(int l,int r){
	int del=log2(r-l+1);
	return min(spsa[l][del],spsa[r-(1<<del)+1][del]);
}
void solve(){
    cin>>s>>q;
    buildyA(s);
    kasai(s);
    sparse();
    // rep(i,0,sz(s)) cout<<sa[i]<<"  ";
    // cout<<endl;
    // rep(i,0,sz(s)-1) cout<<lcp[i]<<"  ";
    // cout<<endl;
    while(q--){
    	int idx,l;
    	cin>>idx>>l;
    	idx--;
    	int pos=inv[idx];
    	int lo=pos,hi=sz(s)-1;
    	while(hi-lo>1){
    		int mid=(lo+hi)/2;
    		if(query_lcp(pos,mid-1)>=l) lo=mid;
    		else hi=mid;
    	}
    	if(query_lcp(pos,hi-1)>=l){
    		cout<<-1<<endl;
    		continue;
    	}
    	int L=hi;
    	lo=L-1;
    	hi=sz(s)-1;
    	while(hi-lo>1){
    		int mid=(lo+hi)/2;
    		if(query_sa(L,mid)+l<=sz(s)) hi=mid;
    		else lo=mid;
    	}
    	if(query_sa(L,hi)+l>sz(s)){
    		cout<<-1<<endl;
    		continue;
    	}
    	L=hi;
		hi=sz(s);
    	while(hi-lo>1){
    		int mid=(lo+hi)/2;
    		if(query_lcp(L,mid-1)>=l) lo=mid;
    		else hi=mid;
    	}
    	int R=lo;
    	cout<<query_sa(L,R)+1<<endl;
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t=1;
    // cin>>t;
    while(t--){
        solve();
    }
    return 0;
}