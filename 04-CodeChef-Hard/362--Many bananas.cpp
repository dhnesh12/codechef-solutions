#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define VV vector
#define pb push_back
#define bitc  __builtin_popcountll
#define m_p make_pair
#define infi 1e18+1
#define eps 0.000000000001
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);
string char_to_str(char c){string tem(1,c);return tem;}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T>//usage rand<long long>()
T rand() {
    return uniform_int_distribution<T>()(rng);
}
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
 
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> oset;
// string to integer stoi()
// string to long long stoll()
// string.substr(position,length);
// integer to string to_string();
 
//////////////
auto clk=clock();
#define all(x) x.begin(),x.end()
#define se second
#define fi first
#define sz(x) ((long long)x.size())
#define int long long  
#define f80 __float128
#define pii pair<int,int>
/////////////
int seg[300000];
int n=100001;
void up(int i, int value) {  
	int in=i;
  for (seg[in += n] += i*value; in > 1; in >>= 1) seg[in>>1] = seg[in] + seg[in^1];
}

int query(int l, int r) {
	++r;
  int res = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l&1) res += seg[l++];
    if (r&1) res += seg[--r];
  }
  return res;
}


signed main()
{
	fastio;
	#ifdef ANIKET_GOYAL
		freopen("inputf.in","r",stdin);
		freopen("outputf.in","w",stdout);
	#endif
	int n;
	cin>>n;
	int tot=0;
	for(int i=1;i<=n;++i)
	{
		int x,y;
		cin>>x>>y;
		tot+=y;
		up(x,y);
	}
	int q;
	cin>>q;
	while(q)
	{
		--q;
		char c;
		cin>>c;
		if(c=='+')
		{
			int x;
			cin>>x;
			up(x,1);
			++tot;
		}
		if(c=='-')
		{
			int x;
			cin>>x;
			up(x,-1);
			--tot;
		}
		if(c=='?')
		{
			int y;
			cin>>y;
			int total=tot*y;
			int consumed=0;
			int l=1,r=1;
			while(1)
			{
				consumed+=(y/l)*(query(l,r));
				if(r==y)
					break;
				l=r+1;
				r=y/(y/l);
			}
			cout<<total-consumed<<"\n";
		}
	}
	#ifdef ANIKET_GOYAL
		cout<<endl<<endl<<endl<<endl<<"Time elapsed: "<<(double)(clock()-clk)/CLOCKS_PER_SEC<<endl;
	#endif
}