#include <bits/stdc++.h>
#define prDouble(x) cout << fixed << setprecision(10) << x
using namespace std;


// #include "boost/algorithm/string.hpp"
// using namespace boost;

#define FastIO ios_base::sync_with_stdio(false)
#define mod 1000000007
#define ll long long int
#define pub push_back
#define fi first
#define sec second
#define read_i(x) scanf("%d",&x)
#define read_s(x) scanf("%s",x)
#define read_l(x) scanf("%ld",&x)
#define INFI 1000000000000000000
#define NINFI -1000000000000000000
#define printNo cout << "no" << '\n';
#define printyes cout << "yes" << '\n';



ll n, k;

string Req_word;

const ll Maxi = ( 1 << 20 ) + 1;

ll PenWritingTheMask[Maxi] = {0};
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	ll t;
	cin >> t;

	while (t--) {

		cin >> n >> k;

		cin >> Req_word;

		memset(PenWritingTheMask, 0, sizeof PenWritingTheMask);

		for (ll i = 1; i <= k; i++) {
			string s;
			cin >> s;
			ll mask = 0;
			for (ll j = 0; j < s.length(); j++) {

				mask |= (1 << (s[j] - 'a'));

			}
			PenWritingTheMask[mask] = i;
		}

		for (ll mask = Maxi; mask >= 0; mask--) {

			if (PenWritingTheMask[mask]) {

				for (ll i = 0; i < 20; i++) {

					if ((mask & (1 << i)) != 0)
						PenWritingTheMask[mask ^ (1 << i)] = PenWritingTheMask[mask];

				}
			}
		}

		ll CurrentMask = 0;
		ll LastWrittenPos = 0;

		for (ll i = 0; i < n; i++) {

			ll Bit_Pos_Of_The_Curr_Char = (1 << (Req_word[i] - 'a'));

			if (PenWritingTheMask[CurrentMask | Bit_Pos_Of_The_Curr_Char]) {

				CurrentMask = CurrentMask | Bit_Pos_Of_The_Curr_Char;

			}
			else {

				ll Pen_that_will_write = PenWritingTheMask[CurrentMask];

				for (ll j = 1; j <= (i - LastWrittenPos); j++) {
					cout << Pen_that_will_write << ' ';
				}

				CurrentMask = 0;
				CurrentMask |= Bit_Pos_Of_The_Curr_Char;
				LastWrittenPos = i;

			}

		}

		ll Pen_that_will_write = PenWritingTheMask[CurrentMask];

		for (ll j = 1; j <= (n - LastWrittenPos); j++) {
			cout << Pen_that_will_write << ' ';
		}

		cout << '\n';


	}
	return 0;
}
