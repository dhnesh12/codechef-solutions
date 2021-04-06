#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse2")
using namespace std;
typedef long long int lld;
typedef vector<lld> vi;
typedef pair<lld,lld> pi;
#define F first
#define S second
#define N 100005
#define MOD 1000000007
#define PB push_back
#define MP make_pair
#define rep(i, a, b) for (lld i = a; i < b; i++)
lld m,t,k,x,y,z,c,q,j,i,r,m1,m2,n,l,d,blocks;

lld segtree[8*N],bit[8*N];

void update(lld node,lld start,lld end,lld idx,lld val){
       if(start==end){
              segtree[node] = val;
              return;
       }
       lld mid = (start+end)/2;
       if(idx<=mid)update(2*node,start,mid,idx,val);
       else update(2*node+1,mid+1,end,idx,val);
       segtree[node] = max(segtree[2*node],segtree[2*node+1]);
}

lld query(lld node,lld start,lld end,lld l,lld r){
       if(l>end||start>r)return -1;
       if(l<=start && end<=r)return segtree[node];
       lld mid = (start+end)/2;
       return max(query(2*node,start,mid,l,r),query(2*node+1,mid+1,end,l,r));
}

void bitupdate(lld idx){
       while(idx<N){
              bit[idx]++;
              idx = idx | (idx+1);
       }
}

lld  bitquery(lld idx){
       lld sum = 0;
       while(idx>0){
              sum += bit[idx];
              idx = (idx&(idx+1))-1;
       }
       return sum;
}

void clean(lld n){
       rep(i,0,8*n)bit[i]=segtree[i]=0;
}


int main(){
       
       ios_base::sync_with_stdio(false);
       cin.tie(NULL);

       cin>>t;
       while(t--){
              cin>>n;
              string s;
              cin>>s;
              s = '@'+s;
              stack<lld>st;
              lld ans = 0;
              rep(i,1,n+1){
                     if(st.empty())st.push(i);
                     else if(s[st.top()]=='4' && s[i] == '7'){
                            lld maxi = query(1,1,n,st.top(),i);
                            lld val = i-2*bitquery(maxi)-1;
                            ans += val;
                            maxi++;
                            update(1,1,n,st.top(),maxi);
                            bitupdate(maxi);
                            st.pop();
                     }
                     else st.push(i);
              }
              cout<<ans<<endl;

              clean(n);
       }

}
/*
1
22
4744477747444777474477
*/