//https://www.codechef.com/viewsolution/44352926

#include <bits/stdc++.h>
#define FAST ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
typedef long long ll;
typedef long double ld;
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define mod 1000000007
#define pii pair<ll,ll>
#define inf 1000000000000000000
#define bpc(x) __builtin_popcountll(x)
#define autoit(x,it) for(auto it = x.begin(); it != x.end(); it++)
#define autoitr(x,it) for(auto it = x.rbegin(); it != x.rend(); it++)
#define rep(n) for(ll i = 0; i < n; i++)
#define repi(i,n) for(ll i = 0; i < n; i++)

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

#define ordered_set tree<ll, null_type,less<ll>, rb_tree_tag,tree_order_statistics_node_update>

using namespace std;
mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

//Height of suffix tree is atmosst log2(N)
//There are around 2*N nodes in the suffix tree
//Each node has atleast 2 children or it is a leaf node
//There are atmost alphabet size( ~ 26 ) children for each node

struct node {
    ll l, r;                                // [L, R-1] boundry for the edge to this node
    ll par;                                 // parent id of the current node, for root = -1
    ll link;                                //suffix link, for v -> s(v)
    map<char, ll> next;                     // pointer id of children nodes
    ll lensum, subcnt;                              // count of substrings starting at this node and sum of their lengths
    map<char, ll> lsum, scnt;

    node (ll l = 0, ll r = 0, ll par = -1)
        : l(l), r(r), par(par), link(-1), lensum(0), subcnt(0) {}
    ll len()  {  return r - l;  }
    ll &get (char c) {
        if (!next.count(c))  next[c] = -1;
        return next[c];
    }
};

struct state {
    ll v, pos;
    state() {}
    state (ll v, ll pos) : v(v), pos(pos)  {}
};

class SuffTree
{
public:
    string s;               //string to build suffix tree on
    vector<node> t;         //nodes of suffix tree structure, node[0] is the root of the tree
    ll n;                   //size of the string
    state ptr;
    ll sz;                  //size - 1 for vector t

    SuffTree(string s)
    {
        this->s = s;
        this->s += '$';
        this->n = this->s.length();
        ptr = state(0, 0);
        t = vector<node>(3*this->n + 10, node());
        build_tree();
        substringCount(0, 0);
    }

    void substringCount(ll id, ll clen)
    {
        if (t[id].next.size() == 0)
            t[id].lensum = (clen * (clen - 1)) / 2, t[id].subcnt = (clen > 1 || t[id].par > 0);
        autoit(t[id].next, it)
        {
            ll l = t[it->ss].len();
            substringCount(it->ss, clen + l);
            t[id].lsum[it->ff] = t[it->ss].lensum, t[id].lensum += t[it->ss].lensum;
            t[id].scnt[it->ff] = t[it->ss].subcnt, t[id].subcnt += t[it->ss].subcnt;
        }
    }

    state go (state st, ll l, ll r) {
        while (l < r)
            if (st.pos == t[st.v].len()) {
                st = state (t[st.v].get( s[l] ), 0);
                if (st.v == -1)  return st;
            }
            else {
                if (s[ t[st.v].l + st.pos ] != s[l])
                    return state (-1, -1);
                if (r - l < t[st.v].len() - st.pos)
                    return state (st.v, st.pos + r - l);
                l += t[st.v].len() - st.pos;
                st.pos = t[st.v].len();
            }
        return st;
    }

    ll split (state st) {
        if (st.pos == t[st.v].len())
            return st.v;
        if (st.pos == 0)
            return t[st.v].par;
        node v = t[st.v];
        //t.pb(node());
        ll id = sz++;
        t[id] = node (v.l, v.l + st.pos, v.par);
        t[v.par].get( s[v.l] ) = id;
        t[id].get( s[v.l + st.pos] ) = st.v;
        t[st.v].par = id;
        t[st.v].l += st.pos;
        return id;
    }

    ll get_link (ll v) {
        if (t[v].link != -1)  return t[v].link;
        if (t[v].par == -1)  return 0;
        ll to = get_link (t[v].par);
        return t[v].link = split (go (state(to, t[to].len()), t[v].l + (t[v].par == 0), t[v].r));
    }

    void tree_extend (ll pos) {
        for (;;) {
            state nptr = go (ptr, pos, pos + 1);
            if (nptr.v != -1) {
                ptr = nptr;
                return;
            }

            ll mid = split (ptr);
            //t.pb(node());
            ll leaf = sz++;
            t[leaf] = node (pos, n, mid);
            t[mid].get( s[pos] ) = leaf;

            ptr.v = get_link (mid);
            ptr.pos = t[ptr.v].len();
            if (!mid)  break;
        }
    }

    void build_tree() {

        this->sz = 1;
        for (ll i = 0; i < n; ++i)
            tree_extend (i);
    }

    ll search(string p)
    {
        if (p.length() == 0)
            return -1;
        ll m = p.length();
        ll pr = 0, id = 0;
        while (pr < m)
        {
            if (t[id].get(p[pr]) == -1)
                return false;
            auto id1 = t[id].get(p[pr]);
            ll len = min(t[id1].len(), m - pr);
            for (ll j = t[id1].l; j < t[id1].l + len; j++)
            {
                if (s[j] != p[pr++])
                    return -1;
            }

            if (pr == m) {
                return t[id1].r - t[id1].len() + len - m;
            }
            id = id1;
        }

        return -1;
    }

    char findRecKth(ll id, ll k, vector<ll> &hold, ll off)
    {
        autoit(t[id].next, it)
        {
            if (it->ff == '$')
                continue;
            if (t[id].lsum[it->ff] - (off * (off + 1)*t[it->ss].subcnt) / 2 < k)
            {
                k -= (t[id].lsum[it->ff] - (off * (off + 1) * t[it->ss].subcnt) / 2);
                continue;
            }

            ll l = t[it->ss].len();
            if (t[it->ss].next.size() == 0)
                l--;

            hold.pb(it->ss);

            if (k > t[it->ss].subcnt * (off * l + (l * (l + 1)) / 2)) {
                k -= (t[it->ss].subcnt * (off * l + (l * (l + 1)) / 2));
                return findRecKth(it->ss, k, hold, off + l);
            }

            ll st = 0, en = l - 1, hi = 0;
            while (en >= st)
            {
                ll mid = (st + en) / 2;
                if ((off * mid + (mid * (mid + 1)) / 2)*t[it->ss].subcnt < k)
                    hi = mid, st = mid + 1;
                else en = mid - 1;
            }

            k -= (t[it->ss].subcnt * (off * hi + (hi * (hi + 1)) / 2));
            k -= ((hi + 1 + off) * ((k - 1) / (hi + 1 + off)));

            autoit(hold, it)
            {
                ll i = (*it);
                if (t[i].len() >= k)
                    return s[t[i].l + k - 1];
                k -= t[i].len();
            }

        }

        return 'a';
    }

    char findKth(ll k)
    {
        vector<ll> hold;
        return findRecKth(0, k, hold, 0);
    }
};

int main()
{
    FAST/**/

    string s;
    cin >> s;

    SuffTree ob(s);

    ll q;
    cin >> q;

    ll sum = 0;

    while (q--)
    {
        ll p, m;
        cin >> p >> m;
        ll k = ((sum % m) * (p % m)) % m + 1;
        char c = ob.findKth(k);
        cout << c << '\n';
        sum += c;
    }


    return 0;
}
