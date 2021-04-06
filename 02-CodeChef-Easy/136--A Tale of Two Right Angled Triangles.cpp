#include<bits/stdc++.h>
using namespace std;
 
typedef    long long          ll;
typedef    vector<long long>    vi; 
typedef    vector<vi>         vvi; 
typedef    pair<long,long>      ii; 
#define    sz(a)              long((a).size()) 
#define    pb                 push_back 
#define    mp                   make_pair
#define    all(c)             (c).begin(),(c).end() 
#define    tr(c,i)            for(typeof((c).begin() i = (c).begin(); i != (c).end(); i++) 
#define    present(c,x)       ((c).find(x) != (c).end()) 
#define    cpresent(c,x)      (find(all(c),x) != (c).end())  
#define    input(v,n)           for(ll i = 0 ; i<n ; i++) cin>>v[i]
#define    output(v,n)          for(ll i = 0 ; i<n ; i++) cout<<v[i]<<" "
#define    ff                     first
#define    ss                   second

int main()
{
    ios_base::sync_with_stdio(false);
      cin.tie(NULL);
      cout.tie(NULL);

      ll t;
      cin>>t;
      while(t--)
      {
        ll a,b,c,d,e,f,l,r;
        cin>>a>>b>>c>>d>>e>>f>>l>>r;
        if(min(a,b)<= min(l,r) && max(a,b) <= max(l,r) && min(d,e)<= min(l,r) && max(d,e) <= max(l,r))
        {
            if(l<r)swap(l,r);
            if( a<= l && b<= r){
                cout<<"0 "<<b<<"\n";
                cout<<a<<" 0\n";
                cout<<"0 0\n";
            } else {
                cout<<b<<" 0\n";
                cout<<"0 "<<a<<"\n";
                cout<<"0 0\n";
            }

             if( d<= l && e<= r){
                cout<<l<<" "<<r-e<<"\n";
                cout<<l-d<<" "<<r<<"\n";
                cout<<l<<" "<<r<<"\n";
            } else {
                swap(d,e);
                cout<<l-d<<" "<<r<<"\n";
                cout<<l<<" "<<r-e<<"\n";
                cout<<l<<" "<<r<<"\n";
            }
        } else {
            cout<<"-1\n";
        }
      }

    return 0;
}