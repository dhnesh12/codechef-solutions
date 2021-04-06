

#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <cstring>
#include <cassert>
#define rf freopen("in.in", "r", stdin)
#define wf freopen("out.out", "w", stdout)
#define rep(i, s, n) for(int i=int(s); i<=int(n); ++i)
using namespace std;
const int mx = 1e5+10, mod = 1e9+7;
#define ff first
#define ss second

int n, t, k;
vector< pair<int, int> > r;
char ans[2111];

int cmp(pair<int, int> l, pair<int, int> r)
{
	return l.ss-l.ff+1 < r.ss-r.ff+1;
}

int main()
{
	//rf;// wf;

	scanf("%d", &t);
	while(t--)
	{
		memset(ans, 0, sizeof ans); r.clear();

		scanf("%d %d", &n, &k);
		rep(i, 1, k)
		{
			int x, y;
			scanf("%d %d", &x, &y);
			r.push_back( make_pair(x, y) );
		}

		rep(i, 1, r.size()-1)
		{
			rep(j, 0, i-1)
			{
				if(r[j].ff >= r[i].ff and r[j].ff <= r[i].ss and r[j].ss >= r[i].ss)
				{
					r.push_back(make_pair(r[i].ff, r[j].ff-1));
					r.push_back(make_pair(r[j].ff, r[i].ss));
					r.push_back(make_pair(r[i].ss+1, r[j].ss));

					r.erase(r.begin()+i); r.erase(r.begin()+j);
					i-=2;
				}
				else if(r[i].ff >= r[j].ff and r[i].ff <= r[j].ss and r[i].ss >= r[j].ss)
				{
					r.push_back(make_pair(r[j].ff, r[i].ff-1));
					r.push_back(make_pair(r[i].ff, r[j].ss));
					r.push_back(make_pair(r[j].ss+1, r[i].ss));

					r.erase(r.begin()+i); r.erase(r.begin()+j);
					i-=2;
				}
			}
		}
		sort(r.begin(), r.end(), cmp);

		rep(i, 0, r.size()-1)
		{
			int cnt = 0;
			rep(j, r[i].ff, r[i].ss)
				if(ans[j] == '\0')
					cnt++;

			for(int j=r[i].ff, chk=0; j<=r[i].ss; ++j)
			{
				if(ans[j] == '\0' and chk < cnt/2)
					ans[j] = '(', chk++;
				else if(ans[j] == '\0' and chk >= cnt/2)
					ans[j] = ')';
			}
		}

		rep(i, 0, n-1)
			if(ans[i] == '\0')
				ans[i] = '(';
		puts(ans);
	}
	return 0;
}

