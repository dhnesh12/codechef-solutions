#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define ll long long
#define ull unsigned long long
#define Toggle(n,i) (n^((ll)1<<i))
#define Check(n,i) (n&((ll)1<<i))
#define Set(n,i) (n|((ll)1<<i))
#define Reset(n,i) (n&(~((ll)1<<i)))
#define fo(a,x,y) for(int i=(x);i<=(y);++i){cout<<a[i]<<" ";}cout<<endl;
#define me(arr,val) memset(arr,val,sizeof arr)
#define inf INT_MAX
#define infd DBL_MAX
#define infl LLONG_MAX
#define mod 1000000007ll
#define f first
#define s second
#define  g(t,a)  (get<a>(t))
#define pra(a) for(auto i:a){cout<<i<<endl;}
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
//int dx[]={+1,-1,0,0};//vertical horizontal
//int dy[]={0,0,+1,-1};//vertical horizontal
//int dx[]={+1,+1,-1,-1,+2,-2,+2,-2};//knights move
//int dy[]={+2,-2,+2,-2,+1,+1,-1,-1};//knights move
//int dx[]={+1,-1,0,0,+1,+1,-1,-1};//vertical horizontal diagonal
//int dy[]={0,0,+1,-1,-1,+1,+1,-1};//vertical horizontal diagonal
using namespace std;
using namespace __gnu_pbds;
/*typedef tree<int, null_type,less<int>, rb_tree_tag,
             tree_order_statistics_node_update>indexed_set;
for set use above*/
typedef tree<pair<int,int>, null_type,less<pair<int, int>>, rb_tree_tag,
tree_order_statistics_node_update> indexed_multiset;
template < typename F, typename S >
ostream& operator << ( ostream& os, const pair< F, S > & p ) {
    return os << "(" << p.first << ", " << p.second << ")";
}
template < typename T >
ostream &operator << ( ostream & os, const vector< T > &v ) {
    os << "{";
    typename vector< T > :: const_iterator it;
    for( it = v.begin(); it != v.end(); it++ ) {
        if( it != v.begin() ) os << ", ";
        os << *it;
    }
    return os << "}";
}
template < typename T >
ostream &operator << ( ostream & os, const set< T > &v ) {
    os << "[";
    typename set< T > :: const_iterator it;
    for ( it = v.begin(); it != v.end(); it++ ) {
        if( it != v.begin() ) os << ", ";
        os << *it;
    }
    return os << "]";
}
template < typename T >
ostream &operator << ( ostream & os, const multiset< T > &v ) {
    os << "[";
    typename multiset< T > :: const_iterator it;
    for ( it = v.begin(); it != v.end(); it++ ) {
        if( it != v.begin() ) os << ", ";
        os << *it;
    }
    return os << "]";
}
template < typename F, typename S >
ostream &operator << ( ostream & os, const map< F, S > &v ) {
    os << "[";
    typename map< F , S >::const_iterator it;
    for( it = v.begin(); it != v.end(); it++ ) {
        if( it != v.begin() ) os << ", ";
        os << it -> first << " = " << it -> second ;
    }
    return os << "]";
}
#define pr(x) cerr << #x << " = " << x << endl;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll t;
    cin>>t;
    for(ll c=1;c<=t;++c)
    {
        ll n,m;
        cin>>n>>m;
        vector<ll>a(n+5);
        vector<ll>b(n+5,0);
        for(ll i=0;i<n;++i)
        {
            cin>>a[i];
        }
        vector<pair<ll,pair<ll,ll>>>seg(m+5);
        for(ll i=0;i<m;++i)
        {
            ll l,r;
            cin>>l>>r>>seg[i].s.s;
            seg[i].f=l-1;
            seg[i].s.f=r-1;
        }
        sort(seg.begin(),seg.begin()+m);
        priority_queue<pair<ll,ll>>pq;
        ll ans=0,flag=1;
        for(ll i=0,j=0;i<n;++i)
        {
            for(;j<seg.size()&&seg[j].f<=i;++j)
            {
                pq.push({seg[j].s.f,seg[j].s.s});
            }
            if(i)
            {
                b[i]+=b[i-1];
            }
            a[i]-=b[i];
            while(!pq.empty()&&a[i]>0)
            {
                ll r,k;
                tie(r,k)=pq.top();
                if(r<i)
                    break;
                pq.pop();
                ll d=min(a[i],k);
                a[i]-=d;
                k-=d;
                ans+=d;
                b[r+1]-=d;
                b[i]+=d;
                if(k)
                {
                    pq.emplace(r,k);
                }
            }
            if(a[i]>0)
            {
                flag=0;
                break;
            }
        }
        if(!flag)
        {
            cout<<"NO"<<endl;
        }
        else
        {
            cout<<"YES "<<ans<<endl;
        }
    }
    return 0;
}
