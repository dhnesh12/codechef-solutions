#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define M 1000000007
#define N 1000016
#define ff first.first
#define fs first.second
#define sf second.first
#define ss second.second
#define f first
#define s second
#define inf 9000000000000000000
ll prime[N];
vector<ll> fact;
pair<ll, ll> tree[N];

void sieve() {

    prime[1] = 1;
    for(ll i=2; i<=1000000; i++) {
        if(!prime[i]) {

            for(ll j=2*i; j<=1000000; j+=i)
                prime[j] = 1;
        }
    }
}

bool chk(ll x) {

    for(ll i=2; i<=sqrt(x); i++) {
        if(x%i==0)
            return false;
    }
    return true;
}

void build(ll node, ll start, ll end) {

    if(start==end) {
        tree[node].s = 1;
        return;
    }

    ll mid = (start + end)/2;
    build(2*node, start, mid);
    build(2*node+1, mid+1, end);

    tree[node].s = tree[2*node].s + tree[2*node+1].s;
}

void update(ll node, ll start, ll end, ll l, ll r, ll x) {

    if(start>end || l>end || start>r)
        return;

    if(start==end) {
        tree[node].s = 0;
        tree[node].f = x;
        return;
    }
    ll mid = (start + end)/2;
    if(tree[2*node].s)
        update(2*node, start, mid, l, r, x);
    if(tree[2*node+1].s)
        update(2*node+1, mid+1, end, l, r, x);

    tree[node].s = tree[2*node].s + tree[2*node+1].s;
    tree[node].f = tree[2*node].f|tree[2*node+1].f;

}

ll query(ll node, ll start, ll end, ll l, ll r) {

    if(start>end || l>end || start>r)
        return 0;

    if(l<=start && r>=end)
        return tree[node].f;

    ll mid = (start + end)/2;
    ll p1 = query(2*node, start, mid, l, r);
    ll p2 = query(2*node+1, mid+1, end, l, r);

    return p1|p2;
}

int main()
{
   ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    ll k,q,n=100000;
    cin>>k>>q;
    sieve();
    for(ll i=1; i<=sqrt(k); i++) {
        if(k%i==0) {
            if(!prime[i])
                fact.push_back(i);

            ll x = k/i;
            if(x==i)
                continue;

            if(x<=1000000) {
                if(!prime[x])
                fact.push_back(x);
            }
            else {
                if(chk(x))
                   fact.push_back(x);
            }
        }
    }

    build(1, 1, n);
    while(q--) {
        char s;
        ll l,r,x;
        cin>>s>>l>>r;
        if(s=='?') {
            ll num = query(1, 1, n, l, r);
            ll cnt = 0;
            for(ll i=0; i<=11; i++) {
                if(num&(1<<i))
                    cnt++;
            }
            cout<<cnt<<"\n";
        }
        else {
            cin>>x;
            ll val = 0;
            for(ll i=0; i<fact.size(); i++) {
                if(x%fact[i]==0)
                    val =(val|(1<<i));
            }
            update(1, 1, n, l, r, val);
        }
    }
    return 0;
}

