/* Author: Gurdeep Singh */
/* Codeforces: gdb_18 , Codechef: gurdeep1810 */
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef long long int ll;
typedef long double ld;
#define mp make_pair
#define ff first
#define ss second
#define bipc __builtin_popcountll		// count number of set bits
#define lb lower_bound				// 1st occurence greater equal to x
#define ub upper_bound				// 1st occurence greater than x 
#define mxe *max_element			// maximum element
#define mne *min_element			// minimum element
#define all(x) x.begin(),x.end()
#define pll pair<ll,ll> 			// pair<ll,ll>
#define vll vector<ll>				// vector<ll>
#define vvll vector<vll>			// vector<vector<ll>>	
#define vpll vector<pll>			// vector<pair<ll,ll>>
#define vvpll vector<vpll>			// vector<vector<pair<ll,ll>>>
#ifndef gdb_18
#define endl '\n' 				// do not use for interactive problems
#endif

/*------------------------------------------- MAPS ----------------------------------------*/
/* map<ll,ll> temp --> insert(mp(a,b)) , size() , empty() , clear() */
/* find(key) returns end() if not found */
/* temp.lower_bound(x) --> for sets and maps */

/*-------------------------------------- PRIORITY QUEUE -----------------------------------*/
#define pqueue priority_queue
/* pqueue<ll> temp --> max heap , pqueue<ll,vll,greater<ll>> temp --> min heap */
/* temp.push() , temp.top() , temp.pop() , temp.size() , temp.empty() */


/*------------------------------------ SETS AND MULTISETS ---------------------------------*/
/* insert() , size() , empty() , lower_bound , upper_bound */
/* temp.lower_bound(x) --> for sets and maps */
/* find(x) iterator to x if exists else end() */
/* erase() deletes element or iterator in set, ALL elements or a iterator in multiset */
/* FIND & ERASE WORK ON ORDERED SETS BUT NOT ON ORDERED MULTISETS */
template<class T> 
using oset=tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
/* less<T> --> set , less_equal<T> --> multiset for increasing order */
/* greater<T> --> set , greater_equal<T> --> multiset for decreasing order */
#define fbo find_by_order 
#define ook order_of_key
/* find_by_order(x) - iterator to xth element (0 indexed) if exists else returns end() */
/* increasing order: order_of_key(x) - number of items strictly lesser than x */
/* decreasing order: order_of_key(x) - number of items strictly greater than x */


/*--------------------------------- STACKS QUEUES AND DEQUES ------------------------------*/
#define pb push_back
#define ppb pop_back()
#define pf push_front
#define ppf pop_front()
/* size() , empty() works for all but clear() works for deque only */
/* stack<ll> --> push() , top() , pop() */
/* queue<ll> --> push() , pop() , front() , back() */
/* deque<ll> --> push_front() , push_back() , pop_front() ,pop_back() , front() , back() */


/*--------------------------------- CONSTANTS AND FUNCTIONS -------------------------------*/
const ll modulo1=1e9+7;
const ll modulo2=998244353;
const ll inf=1e18;
const ld pi=acos(-1);
inline ll power(ll a,ll b,ll m)
{
	ll res=1;
	while(b)
	{
		if(b&1) res=(res*a)%m; 
		a=(a*a)%m; b>>=1;
	}
	return res%m;
}
inline ll inv(ll a,ll m)
{
	return power(a,m-2,m);
}

/*-------------------------------------- CODE BEGINS --------------------------------------*/

const ll N=5e5+5;
const ll M=1e2+5;		
ll mod=modulo1;					

bool iv(ll x,ll y,ll z,ll p,ll q)
{
	ll tt=x+y+z;
	ll xx=max(x,max(y,z));
	tt-=xx;
	if(tt<=xx)
		return false;
	ll tt1=((y*y) + (z*z) - (x*x))*q;
	ll tt2=(2*p*y*z);
	if(tt1>=tt2)
		return true;
	return false;
}

bool iv1(ll x1,ll y1,ll z1,ll x2,ll y2,ll z2)
{
	ll tt1=((y1*y1) + (z1*z1) - (x1*x1))*(y2*z2);
	ll tt2=((y2*y2) + (z2*z2) - (x2*x2))*(y1*z1);
	if(tt1>tt2)
		return true;
	return false;
}

void solve()
{
	ll n,p,q;
	cin>>n>>p>>q;
	vpll arr(n);
	for(ll i=0;i<n;i++)
	{
		ll a;
		cin>>a;
		arr[i]=mp(a,i+1);
	}
	if(n<3)
	{
		cout<<-1<<endl;
		return;
	}
	sort(all(arr));
	ll x1=-1,y1=-1,z1=-1;
	bool chk=false;
	for(ll i=0;i<n;i++)
	{
		for(ll j=0;j<n;j++)
		{
			if(i==j)
				continue;
			auto it=lb(all(arr),mp(abs(arr[i].ff-arr[j].ff),inf));
			ll te=it-arr.begin();
			ll lo=te,hi=n-1;
			while(lo<hi)
			{
				ll mid=(lo+hi+1)/2;
				if(iv(arr[mid].ff,arr[i].ff,arr[j].ff,p,q))
					lo=mid;
				else
					hi=mid-1;
			}
			if(lo==max(i,j))
				lo--;
			if(lo==min(i,j))
				lo--;
			if(lo<te)
				continue;
			if(!iv(arr[lo].ff,arr[i].ff,arr[j].ff,p,q))
				continue;
			if(!chk)
			{
				chk=true;
				x1=lo;
				y1=i;
				z1=j;
			}
			else
			{
				if(iv1(arr[x1].ff,arr[y1].ff,arr[z1].ff,arr[lo].ff,arr[i].ff,arr[j].ff))
				{
					x1=lo;
					y1=i;
					z1=j;
				}
			}
		}
	}
	if(!chk)
		cout<<-1<<endl;
	else
		cout<<arr[x1].ss<<" "<<arr[y1].ss<<" "<<arr[z1].ss<<endl;
	return;
}

void precompute()
{
	// cout<<fixed<<setprecision(10);
	
	return;
}

/*--------------------------------------- CODE ENDS ---------------------------------------*/
signed main()
{
	clock_t clk=clock();
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	#ifdef gdb_18
		freopen("input.txt","rt",stdin);
		freopen("output.txt","wt",stdout);
	#endif
	precompute();
	ll test=1;
	cin>>test;
	for(ll i=1;i<=test;i++)
	{
		// cout<<"Case #"<<i<<": ";
		// cout<<endl;
		solve();
	}
	#ifdef gdb_18
	cerr<<"Execution Time : "<<(1000.0*((ld)(clock()-clk))/(ld)CLOCKS_PER_SEC)<<"ms\n";
	#endif
	return 0;	
}
/*-----------------------------------------------------------------------------------------*/