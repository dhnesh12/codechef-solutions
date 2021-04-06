#include <bits/stdc++.h>
using namespace std;
#pragma optimize("-O3")
#define int long long int
#define f first
#define s second
#define pb push_back
#define endl '\n'

const int N=100;
int tot=0;
int t1[40005];
int t2[40005];
int cnt[10005];
int vals[10005];

int sum1(int v, int tl, int tr, int l, int r) {
    if (l > r) 
        return 0;
    if (l == tl && r == tr) {
        return t1[v];
    }
    int tm = (tl + tr) / 2;
    return sum1(v*2, tl, tm, l, min(r, tm))
           + sum1(v*2+1, tm+1, tr, max(l, tm+1), r);
}


void update1(int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
        t1[v] = new_val;
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            update1(v*2, tl, tm, pos, new_val);
        else
            update1(v*2+1, tm+1, tr, pos, new_val);
        t1[v] = t1[v*2] + t1[v*2+1];
    }
}



int sum2(int v, int tl, int tr, int l, int r) {
    if (l > r) 
        return 0;
    if (l == tl && r == tr) {
        return t2[v];
    }
    int tm = (tl + tr) / 2;
    return sum2(v*2, tl, tm, l, min(r, tm))
           + sum2(v*2+1, tm+1, tr, max(l, tm+1), r);
}


void update2(int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
        t2[v] = new_val;
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            update2(v*2, tl, tm, pos, new_val);
        else
            update2(v*2+1, tm+1, tr, pos, new_val);
        t2[v] = t2[v*2] + t2[v*2+1];
    }
}


bool comp(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b){
	int ga=a.f.f/N;
	int gb=b.f.f/N;
	if(ga==gb){
		return (ga & 1) ? a.f.s <b.f.s : a.f.s > b.f.s;
	}
	else{
		return a.f.f<b.f.f;
	}
}    





main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int g;
	cin>>g;
	while(g--){
		int n;
		cin>>n;
		int arr[n];
		set<int>se;
		for(int i=0; i<n; i++){
			cin>>arr[i];
			se.insert(arr[i]);
		}
		int q;
		cin>>q;
		vector<pair<pair<int, int>, int>>qu;
		for(int i=0; i<q; i++){
			int l, r;
			cin>>l>>r;
			l--;
			r--;
			qu.pb({{l, r}, i});
		}
		sort(qu.begin(), qu.end(), comp);
		int ans[q];
		int cur_l=0;
		int cur_r=-1;
		map<int, int>ma;
		int pt=0;
		for(auto u:se){
			ma[u]=pt;
			vals[pt]=u;
			pt++;
		}
		for(int i=0; i<n; i++){
			arr[i]=ma[arr[i]];
		}
		for(auto u:qu){
			int ind=u.s;
			int l=u.f.f;
			int r=u.f.s;
			while(cur_l>l){
				cur_l--;
				if(cnt[arr[cur_l]]>0){
					cnt[arr[cur_l]]++;
					continue;
				}
				else{
					cnt[arr[cur_l]]++;
					int v1=sum1(1, 0, 10000, 0, arr[cur_l]);
					tot+=(v1+1)*vals[arr[cur_l]];
					int v2=sum2(1, 0, 10000, arr[cur_l], 10000);
					tot+=v2;
					update1(1, 0, 10000, arr[cur_l], 1);
					update2(1, 0, 10000, arr[cur_l], vals[arr[cur_l]]);
				}
			}
			while(cur_r<r){
				cur_r++;
				if(cnt[arr[cur_r]]>0){
					cnt[arr[cur_r]]++;
					continue;
				}
				else{
					cnt[arr[cur_r]]++;
					int v1=sum1(1, 0, 10000, 0, arr[cur_r]);
					tot+=(v1+1)*vals[arr[cur_r]];
					int v2=sum2(1, 0, 10000, arr[cur_r], 10000);
					tot+=v2;
					update1(1, 0, 10000, arr[cur_r], 1);
					update2(1, 0, 10000, arr[cur_r], vals[arr[cur_r]]);
				}
			}
			while(cur_l<l){
				if(cnt[arr[cur_l]]>1){
					cnt[arr[cur_l]]--;
					cur_l++;
					continue;
				}
				cnt[arr[cur_l]]--;
				int v1=sum1(1, 0, 10000, 0, arr[cur_l]);
				tot-=(v1)*vals[arr[cur_l]];
				int v2=sum2(1, 0, 10000, arr[cur_l]+1, 10000);
				tot-=v2;
				update1(1, 0, 10000, arr[cur_l], 0);
				update2(1, 0, 10000, arr[cur_l], 0);
				cur_l++;
			}
			while(cur_r>r){
				if(cnt[arr[cur_r]]>1){
					cnt[arr[cur_r]]--;
					cur_r--;
					continue;
				}
				cnt[arr[cur_r]]--;
				int v1=sum1(1, 0, 10000, 0, arr[cur_r]);
				tot-=v1*vals[arr[cur_r]];
				int v2=sum2(1, 0, 10000, arr[cur_r]+1, 10000);
				tot-=v2;
				update1(1, 0, 10000, arr[cur_r], 0);
				update2(1, 0, 10000, arr[cur_r], 0);
				cur_r--;
			}
			ans[ind]=tot;
		}
		for(int i=0; i<q; i++){
			cout<<ans[i]<<endl;
		}
		tot=0;
		for(int i=0; i<40005; i++){
			t1[i]=0;
			t2[i]=0;
		}
		for(int i=0; i<10005; i++){
			vals[i]=0;
			cnt[i]=0;
		}
	}
	return 0;
}