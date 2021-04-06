#include <bits/stdc++.h>
using namespace std;

long long cnt;

bool solve(vector<long long> v,vector<long long> a,long long k)
{
	if(a.size()==1)
	{
		return 1;
	}

	if(a[0]>a[1])
	{
		v.push_back(a[0]);
	}

	else
	{
		if(a[1]-a[0]<=k)
		{
			cnt++;
			v.push_back(a[0]);
		}

		else
		{
			return 0;
		}
	}

	for (long long i = 2; i < a.size()-1;i+=2)
	{
		long long j = i + 1;

		if(max(a[i],a[j])<v[0])
		{
			v.push_back(max(a[i], a[j]));
		}

		else
		{
			if(max(a[i],a[j])-v[0]<=k)
			{
				v.push_back(max(a[i], a[j]));
			}

			else
			{
				if(abs(a[i]-a[j])<=k)
				{
					cnt++;
					v.push_back(min(a[j], a[i]));
				}

				else
				{
					return 0;
				}
			}
		}
	}

	vector<long long> t;
	return (solve(t, v,k));
}

int main()
{
	int t;
	cin >> t;
	while(t--)
	{
		long long h,k;
		cin >> h >> k;
		vector<long long> a(pow(2, h));
		for (int i = 0; i < a.size();i++)
		{
			cin >> a[i];
		}

		vector<long long> v;
		cnt = 0;
		if (solve(v, a, k))
			cout << cnt << endl;
		else
			cout << -1 << endl;
	}

	return 0;
}
