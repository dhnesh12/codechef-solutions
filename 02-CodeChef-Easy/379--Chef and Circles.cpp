#include<bits/stdc++.h>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int n ,q;
	cin >> n >> q;
	double x[n],y[n],r[n];
	int prefix_arr[1000001]= {0};
	for(int i=0; i<n; i++)
	{
		cin >> x[i] >> y[i] >> r[i];
	}
	for(int i=0; i<n; i++)
	{
		for(int j=i+1; j<n; j++)
		{
			double d = sqrt((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]));
			double r1 =(double) max(r[i], r[j]);
			double r2 =(double) min(r[i], r[j]);
			double max_val, min_val;
			if(d > r1 + r2) min_val = d - r1 - r2;
			else if( r1 > r2+ d) min_val = r1-r2-d;
			else min_val = 0;
			max_val = d + r1 + r2;
			prefix_arr[(int)ceil(min_val)]++;
			prefix_arr[(int)floor(max_val+1)]--;
		}
	}
	for(int i=1; i<1000001; i++)
	{
		prefix_arr[i] += prefix_arr[i-1];
	}
	while(q--)
	{
		int k ;
		cin >> k;
		cout << prefix_arr[k] << "\n";
	}
	
	return 0;
}