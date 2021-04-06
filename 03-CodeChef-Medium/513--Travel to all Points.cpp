/*

                         YATIN KWATRA                  _03_08_14


Let's Hoop..


I wanna to play a game....   :)


				 ─────▄██▀▀▀▀▀▀▀▀▀▀▀▀▀██▄─────
				 ────███───────────────███────
				 ───███─────────────────███───
				 ──███───▄▀▀▄─────▄▀▀▄───███──
				 ─████─▄▀────▀▄─▄▀────▀▄─████─
				  ████──▄████─────████▄──█████
				 █████─██▓▓▓██───██▓▓▓██─█████
				 █████─██▓█▓██───██▓█▓██─█████
				 █████─██▓▓▓█▀─▄─▀█▓▓▓██─█████
				 ████▀──▀▀▀▀▀─▄█▄─▀▀▀▀▀──▀████
				 ███─▄▀▀▀▄────███────▄▀▀▀▄─███
				 ███──▄▀▄─█──█████──█─▄▀▄──███
				 ███─█──█─█──█████──█─█──█─███
				 ███─█─▀──█─▄█████▄─█──▀─█─███
				 ███▄─▀▀▀▀──█─▀█▀─█──▀▀▀▀─▄███
				 ████─────────────────────████
				 ─███───▀█████████████▀───████
				 ─███───────█─────█───────████
				 ─████─────█───────█─────█████
				 ───███▄──█────█────█──▄█████─
				 ─────▀█████▄▄███▄▄█████▀─────
				 ──────────█▄─────▄█──────────
				 ──────────▄█─────█▄──────────
				 ───────▄████─────████▄───────
				 ─────▄███████───███████▄─────
				 ───▄█████████████████████▄───
				 ─▄███▀───███████████───▀███▄─
				 ███▀─────███████████─────▀███
				 ▌▌▌▌▒▒───███████████───▒▒▐▐▐▐
				 ─────▒▒──███████████──▒▒─────
				 ──────▒▒─███████████─▒▒──────
				 ───────▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒───────
				 ─────────████░░█████─────────
				 ────────█████░░██████────────
				 ──────███████░░███████───────
				 ─────█████──█░░█──█████──────
				 ─────█████──████──█████──────
				 ──────████──████──████───────
				 ──────████──████──████───────
				 ──────████───██───████───────
				 ──────████───██───████───────
				 ──────████──████──████───────
				 ─██────██───████───██─────██─
				 ─██───████──████──████────██─
				 ─███████████████████████████─
				 ─██─────────████──────────██─
				 ─██─────────████──────────██─
				 ────────────████─────────────
				 ─────────────██──────────────

------------------------------------------------


*/

// AC BAKSHI RABBA

// #pragma GCC optimize "trapv"

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll                      long long
#define int                     ll
#define FIO                     ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define ld                      long double
#define ull                     unsigned long long
#define endl                    "\n"
#define fo(i,a,b)               for(int i = a; i<=b ; i++)
#define rfo(i,a,b)              for(int i = a; i>=b ; i--)
#define vii                     vector<int>
#define vll                     vector<ll>
#define pq                      priority_queue
#define uom                     unordered_map
#define all(v)                  v.begin(),v.end()
#define mp                      make_pair
#define pb                      push_back
#define pob                     pop_back
#define ff                      first
#define ss                      second
#define pii                     pair<int,int>
#define mii                     map<int,int>
#define vvii                    vector<vii>
#define mod                     1000000007
#define MIN                     -1e9
#define pi                      3.1415926535897932384626433832795
#define cz(x)                   63 - __builtin_clzll(x)

using namespace std;
using namespace __gnu_pbds;

template<class T> using oset =  tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;


void INPUT()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
}

/*
----------------------------------------------------------------

   -> Check For Overflows
   -> Out of Bounds
   -> Initialisations of global arrays and variables
   -> Read the Question and the sample test cases carefully
   -> Its not Always Complex, Try to simplify
   -> write it down and try to solve
   -> Have Faith in urself and in ur approach
   -> If it seems totally out of reach, switch to next :)
   -> And Come Back later, if possible ..

----------------------------------------------------------------*/

const int N = 1e6 + 5;
array<int, 2>v[N];
int a, b, c, d, n;
int par[N];

int sup(int node)
{
	if (par[node] == node) return node;
	return par[node] = sup(par[node]);
}

int dis(array<int, 2> &p1, array<int, 2>&p2)
{
	return (llabs(p1[0] - p2[0]) + llabs(p1[1] - p2[1]));
}

bool possible(int x)
{
	fo(i, 0, n - 1) par[i] = i;

	fo(i, 0, n - 1)
	{
		if (dis(v[a], v[i]) >= x) par[sup(i)] = sup(a);
		if (dis(v[b], v[i]) >= x) par[sup(i)] = sup(b);
		if (dis(v[c], v[i]) >= x) par[sup(i)] = sup(c);
		if (dis(v[d], v[i]) >= x) par[sup(i)] = sup(d);
	}

	fo(i, 0, n - 1) if (sup(i)^sup(0)) return 0;
	return 1;

}

void solve()
{
	cin >> n;

	fo(i, 0, n - 1) cin >> v[i][0] >> v[i][1];

	// Find the four corner points

	a = b = c = d = 0;

	fo(i, 0, n - 1)
	{
		if ((v[i][0] + v[i][1]) > (v[a][0] + v[a][1])) a = i;
		if ((v[i][0] - v[i][1]) > (v[b][0] - v[b][1])) b = i;
		if ((-v[i][0] - v[i][1]) > (-v[c][0] - v[c][1])) c = i;
		if ((-v[i][0] + v[i][1]) > (-v[d][0] + v[d][1])) d = i;
	}

	int low = 0, high = 1e18, ans, mid;

	while (low <= high)
	{
		mid = (low + high) / 2;
		if (possible(mid))
		{
			ans = mid;
			low = mid + 1;
		}
		else high = mid - 1;
	}

	cout << ans << endl;
}

signed main() {

	FIO
	INPUT();

	int t;
	t = 1;
	cin >> t;

	fo(i, 0, t - 1)
	{
		solve();
	}

	return 0;
}
