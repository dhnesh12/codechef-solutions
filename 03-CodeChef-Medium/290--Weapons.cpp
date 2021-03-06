#include <bits/stdc++.h>
using namespace std;

const int N = 1<<8;

#define ld long double
#define ll long long
long double dp[N][8];
long double coord[N][8][2];

ld calc(ld vx, ld vy, ld x1, ld y1, ld x2, ld y2, ld sp)
{
	ld p = x2-x1,q=y2-y1;
	return (p*vx+q*vy+sqrt((p*vx+q*vy)*(p*vx+q*vy)+(sp*sp-vx*vx-vy*vy)*(p*p+q*q)))/(sp*sp-vx*vx-vy*vy);
}

struct point {
	ld x, y;
};
point d[8];
point initd[8];

struct vel {
	ld dx, dy;
};

point expd; ld s;
vel v[8];

ld tsp(int n) {
	int num = (1<<n);
	for(int msk=1; msk<num; msk++)
		for(int i=0; i<n; i++)
			dp[msk][i] = 1e18;

	for(int msk=1; msk<num; msk++) {
		for(int i=0; i<n; i++) {
			if(!(msk & (1<<i)))
				continue;
			if(msk == (1<<i)) {
				dp[msk][i] = calc(v[i].dx, v[i].dy, expd.x, expd.y, initd[i].x, initd[i].y, s) + 1;
			}
			else {
				for(int j=0; j<n; j++) {
					if(i==j || (!(msk & (1<<j))))
						continue;
					ld f = dp[msk^(1<<i)][j] + calc(v[i].dx, v[i].dy,coord[msk^(1<<i)][j][0],coord[msk^(1<<i)][j][1],initd[i].x + v[i].dx*dp[msk^(1<<i)][j], initd[i].y+v[i].dy*dp[msk^(1<<i)][j], s) + 1;
					// cout << msk << " " << i << " " << j << " " << f << endl;
					dp[msk][i] = min(dp[msk][i], f);
				}
			}
			// cout << msk << " " << i << " " << dp[msk][i] << endl;
			coord[msk][i][0] = initd[i].x + v[i].dx * dp[msk][i];
			coord[msk][i][1] = initd[i].y + v[i].dy * dp[msk][i];
		}
	}

	long double ans = 1e18;
	for(int i=0; i<n; i++)
		ans = min(ans, dp[num-1][i] + calc(0., 0., coord[num-1][i][0], coord[num-1][i][1], expd.x, expd.y, s));

	return ans;

} 

ll rnext(ld x)
{
	return floor(x+0.99999999999999);
}

int main() {
	
	int k = 1;

	while(1)
	{
		int n;
		cin>>n;
		if(n==0)
		{
			break;
		}
		for(int i = 0;i<n;i++)
		{
			cin>>d[i].x>>d[i].y>>v[i].dx>>v[i].dy;
			
			initd[i].x = d[i].x;
			initd[i].y=d[i].y;
		}
		cin>>expd.x>>expd.y>>s;

		ld x0 = expd.x,y0=expd.y;
		ld ans = tsp(n) * 3600.;
		ll time_taken = rnext(ans);

		ll a = time_taken/3600;
		ll b = (time_taken-a*3600)/60;
		ll c = time_taken-a*3600-b*60;
		cout << k << " " << a << " " << b << " " << c << endl;
		k++;
	}
}
