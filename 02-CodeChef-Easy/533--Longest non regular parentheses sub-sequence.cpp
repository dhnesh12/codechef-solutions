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

string s;
int k,n;

bool regular()
{
    stack<char>stk;
    for(int i=0;i<n;++i)
    {
        if(s[i]=='(')
        {
            stk.push('(');
        }
        else
        {
            if(stk.empty())
            {
                return false;
            }
            stk.pop();
        }
    }
    if(stk.size())
        return false;
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin>>t;
    for(int c=1;c<=t;++c)
    {
        int flag=1;
        cin>>s>>k;
        n=s.length();
        if(!regular())
        {
            if(k>1)
                flag=0;
        }
        else
        {
            vector<int>l,r;
            s+='2';
            for(int i=0;i<n;++i)
            {
                int start=i;
                while(s[i]==s[i+1])
                {
                    ++i;
                }
                if(s[start]=='(')
                {
                    l.emplace_back(start);
                }
                else
                {
                    r.emplace_back(start);
                }
            }
            s.pop_back();
            //pr(s);
            //pr(l);
            //pr(r);
            int total=l.size()*2;
            reverse(l.begin(),l.end());
            if(k>total)
            {
                flag=0;
            }
            else if(k<=total/2)
            {
                s.erase(r[k-1],1);
            }
            else
            {
                k-=total/2;
                s.erase(l[k-1],1);
            }
        }
        if(!flag)
        {
            cout<<"-1"<<endl;
        }
        else
        {
            cout<<s<<endl;
        }
    }
    return 0;
}
