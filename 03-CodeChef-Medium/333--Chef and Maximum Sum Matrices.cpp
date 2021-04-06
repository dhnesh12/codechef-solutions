#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>
#include <limits.h>
#include <string>
#include <cstring>
#include <queue>
#define rf freopen("in.in", "r", stdin)
#define wf freopen("out.out", "w", stdout)
#define rep(i, s, n) for(int i=int(s); i<=int(n); ++i)
using namespace std;
const int mx = 1e5 + 10, mod = 1e9+7;

vector<int> l[10];
int low_high[10][2];
int cnt_sum[10][2];
int z_nz[10][2];

void calc_low_high(vector<int> v, int idx)
{
	low_high[idx][1] = INT_MIN, cnt_sum[idx][1] = 0;
	low_high[idx][0] = INT_MAX, cnt_sum[idx][0] = 0;
	z_nz[idx][0] = 0;

	for(int i = 0; i<v.size(); ++i)
	{
		int current_sum = 0;
		for(int j = i; j<v.size(); ++j)
		{
			current_sum += v[j];
			if(current_sum == 0)
				z_nz[idx][0] += 1;

			if(current_sum > low_high[idx][1])
				low_high[idx][1] = current_sum, cnt_sum[idx][1] = 1;
			else if(current_sum == low_high[idx][1])
				cnt_sum[idx][1] += 1;

			if(current_sum < low_high[idx][0])
				low_high[idx][0] = current_sum, cnt_sum[idx][0] = 1;
			else if(current_sum == low_high[idx][0])
				cnt_sum[idx][0] += 1;
		}
	}
	
	if(low_high[idx][0] == low_high[idx][1])
		cnt_sum[idx][0] = 0;

	z_nz[idx][1] = (v.size()*(v.size()+1))/2 - z_nz[idx][0];
}

int main()
{
	//rf; wf;
	ios::sync_with_stdio(0);
	
	int t;
	cin >> t;
	while(t--)
	{
		int n;
		cin >> n;
		rep(i, 1, n)
		{
			int len;
			cin >> len;
			
			l[i].clear();

			rep(j, 1, len)
			{
				int in;
				cin >> in;
				l[i].push_back(in);
			}
			

			calc_low_high(l[i], i);
		}
		
		long long max_sum = LLONG_MIN;
		int number_of_submatrices = 0;
		
		rep(i, 0, (1<<n)-1)
		{
			long long temp_sum = 1;
			int temp_count = 1;

			rep(j, 0, n-1)
			{
				int bit = (i & (1<<j)) > 0;
				temp_sum *= low_high[j+1][bit];
				temp_count = (1ll*temp_count*cnt_sum[j+1][bit])%mod;
			}

			if(temp_sum > max_sum and temp_count)
			{
				max_sum = temp_sum,
				number_of_submatrices = temp_count;
			}
			else if(temp_sum == max_sum)
				number_of_submatrices = (number_of_submatrices+temp_count)%mod;
		}

		if(max_sum != 0)
		{
			cout << max_sum << ' ' << number_of_submatrices << '\n';
			continue;
		}

		number_of_submatrices = 0;
		rep(i, 1, (1<<n)-1)
		{
			int temp_count = 1;
			rep(j, 0, n-1)
			{
				int bit = (i & (1<<j)) == 0;
				temp_count = (1ll*temp_count*z_nz[j+1][bit])%mod;
			}

			number_of_submatrices = (number_of_submatrices+temp_count)%mod;
		}
		cout << max_sum << ' ' << number_of_submatrices << '\n';
	}
	return 0;
}