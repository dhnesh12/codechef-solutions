#include <bits/stdc++.h>
#define int long long
using namespace std;


const int maxn = 2e7+10;
const int inf = 1e18;


int n,V(1),ans(0);
int nxt[maxn][2],p[maxn],cnt[maxn],arr[maxn],dpl[maxn],dpr[maxn];

void add(int id,int val,int pos){
    int cur = ((val>>pos)&1);
    if(nxt[id][cur] == 0){
        nxt[id][cur] = ++V;
        p[V] = id;
    }
    if(pos == 0){
        cnt[nxt[id][cur]]++;
        return;
    }
    add(nxt[id][cur],val,pos-1);
}


void erase_val(int id,int val,int pos){
    if(pos == -1){
        cnt[id]--;
        if(cnt[id] > 0) return;
        pos = 0;
        for(int v = id;v != 1;v = p[v]){
            nxt[p[v]][((val>>pos)&1)] = 0;
            if(nxt[p[v]][1-((val>>pos)&1)] != 0) break;
            pos++;
        }
        return;
    }
    int cur = ((val>>pos)&1);
    erase_val(nxt[id][cur],val,pos-1);
}


void solve(int id,int val,int pos){
    if(pos == -1) return;
    int cur = ((val>>pos)&1);
    if(nxt[id][1-cur] != 0){
        ans += (1ll<<pos);
        solve(nxt[id][1-cur],val,pos-1);
    }
    else{
        solve(nxt[id][cur],val,pos-1);
    }
}


int32_t main(){
    ios:: sync_with_stdio(0),cin.tie(0),cout.tie(0);
    ////////////////////////////////////////////////
    cin >> n;
    for(int i = 0;i<n;i++){
        cin >> arr[i];
    }
    int cur = arr[0];
    dpl[0] = cur;
    add(1,cur,55);
    for(int i = 1;i<n;i++){
        ans = 0;
        solve(1,(cur^arr[i]),55);
        dpl[i] = max(dpl[i-1],ans);
        cur ^= arr[i];
        add(1,cur,55);
    }
    int ans1 = arr[0];
    int cur1 = arr[0];
    dpl[0] = max(dpl[0],ans1);
    for(int i = 1;i<n;i++){
        cur1 ^= arr[i];
        ans1 = max(ans1,cur1);
        dpl[i] = max(dpl[i],ans1);
    }
    reverse(arr,arr+n);
    cur = arr[0];
    dpr[0] = cur;
    for(int i = 0;i<V+10;i++){
        nxt[i][0] = nxt[i][1] = 0;
    }
    add(1,cur,55);
    for(int i = 1;i<n;i++){
        ans = 0;
        solve(1,(cur^arr[i]),55);
        dpr[i] = max(dpr[i-1],ans);
        cur ^= arr[i];
        add(1,cur,55);
    }
    int ans2 = arr[0];
    int cur2 = arr[0];
    dpr[0] = ans2;
    for(int i = 1;i<n;i++){
        cur ^= arr[i];
        ans2 = max(ans2,cur2);
        dpr[i] = max(dpr[i],ans2);
    }
    int answer = 0;
    for(int i = 0;i<n;i++){
        answer = max(answer,dpl[i]+dpr[n-2-i]);
    }
    cout << answer << "\n";
}
