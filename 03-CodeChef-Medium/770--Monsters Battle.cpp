// tierlistofpeople.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <set>

using namespace std;

#define ll long long

int n[2], a[100000];
ll play(ll s1, ll s2, multiset<int>& attack1, multiset<int>& defense1, multiset<int>& attack2, multiset<int>& defense2) 
{
	ll r = s1 - s2;
	if (!attack1.empty() && !defense2.empty()) 
	{
		int monster1 = *attack1.begin(), monster2 = *--defense2.end();
		attack1.erase(attack1.find(monster1));
		defense1.insert(monster1);
		s2 -= monster2;
		defense2.erase(defense2.find(monster2));
		r = max(-play(s2, s1, attack2, defense2, attack1, defense1), r);
	}
	return r;
}

void solve() {
	cin >> n[0] >> n[1];
	ll s[2] = {};
	multiset<int> attack[2], defense[2];
	for (int k : {0, 1}) 
	{
		for (int i = 0; i < n[k]; ++i)
		{
			cin >> a[i];
		}
		string t;
		cin >> t;

		for (int i = 0; i < n[k]; ++i) 
		{
			if (t[i] == 'A')
			{
				attack[k].insert(a[i]);
			}
			else
			{
				defense[k].insert(a[i]);
			}
			s[k] += a[i];
		}
	}

	cout << play(s[0], s[1], attack[0], defense[0], attack[1], defense[1]) << "\n";
}

int main() 
{
	int t;
	cin >> t;
	while (t--)
	{
		solve();
	}
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
