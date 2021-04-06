#include <bits/stdc++.h>
#define ll long long
#define lld long double
#define MOD 1000000007
#define CAP 10000000
#define inf 1e+18
#define pii pair<ll,ll>
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define endl '\n'
#define sz(v) v.size()
#define all(v)    v.begin(),v.end()
#define fast  ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;
ll power(ll x,ll y, ll md=MOD){ll res = 1;x%=md;while(y>0){if(y&1)res = (res*x)%md;x = (x*x)%md;y = y>>1;}return res%md;}

#define int ll

inline bool inRange(int a, int b, int x) {
	return (a<=x) && (x<=b);
}

inline int count(int x, int c) {
	int ans = 0;
	while(x) {
		if(x%10==c) ans++;
		x/=10;
	}
	return ans;
}

vector<int> get(int a, int b, int c) {
	set<int> ans;

	if(a==b) {
		return vector<int>(1,a);
	}
	else if(a+1==b) {
		int c1 = count(a,c);
		int c2 = count(b,c);
		if(c1>=c2) ans.insert(a);
		if(c2>=c1) ans.insert(b);

		vector<int> res;
		res.assign(all(ans));
		return res;
	}

	for(int i=1e+9;i>=1;i/=10) {
		int a1 = (a/i);
		int b1 = (b/i);

		if(b1-a1>1) {
			int mx = 0;

			for(int k1=i;k1>=1;k1/=10) {
				int dig = (a/k1)%10;
				if(dig==9) continue;

				int val2 = (a/(10*k1))*(10*k1) + (((k1*10)-1)/9)*c;

				for(int j1=1;j1<=k1;j1*=10)
				for(int j=0;j<10;j++) {
					int temp = val2 + (j1)*(j-c);
					if(inRange(a,b,temp)) mx = max(mx, count(temp,c));
				}

				break;
			}

			int temp = a;
			if(inRange(a,b,temp)) mx = max(mx, count(temp,c));

			for(int k1=i;k1>=1;k1/=10) {
				int dig = (b/k1)%10;
				if(dig==0) continue;

				int val2 = (b/(10*k1))*(10*k1) + (((k1*10)-1)/9)*c;

				for(int j1=1;j1<=k1;j1*=10)
				for(int j=0;j<10;j++) {
					int temp = val2 + (j1)*(j-c);
					if(inRange(a,b,temp)) mx = max(mx, count(temp,c));
				}

				break;
			}

			temp = b;
			if(inRange(a,b,temp)) mx = max(mx, count(temp,c));

			// mx done

			for(int k1=i;k1>=1;k1/=10) {
				int dig = (a/k1)%10;
				if(dig==9) continue;

				int val2 = (a/(10*k1))*(10*k1) + (((k1*10)-1)/9)*c;

				for(int j1=1;j1<=k1;j1*=10)
				for(int j=0;j<10;j++) {
					int temp = val2 + (j1)*(j-c);
					if(inRange(a,b,temp) && mx == count(temp,c)) ans.insert(temp);
				}

				break;
			}

			temp = a;
			if(inRange(a,b,temp) && mx == count(temp,c)) ans.insert(temp);

			for(int k1=i;k1>=1;k1/=10) {
				int dig = (b/k1)%10;
				if(dig==0) continue;

				int val2 = (b/(10*k1))*(10*k1) + (((k1*10)-1)/9)*c;

				for(int j1=1;j1<=k1;j1*=10)
				for(int j=0;j<10;j++) {
					int temp = val2 + (j1)*(j-c);
					if(inRange(a,b,temp) && mx == count(temp,c)) ans.insert(temp);
				}

				break;
			}

			temp = b;
			if(inRange(a,b,temp) && mx == count(temp,c)) ans.insert(temp);

			vector<int> res;
			res.assign(all(ans));
			return res;
		}
	}
}

signed main() {
	fast;

	int t;
	cin>>t;
	while(t--) {
		int a,b,c,d;
		cin>>a>>b>>c>>d;

		vector<int> v1 = get(a,b,c);
		vector<int> v2 = get(a,b,d);

		sort(all(v1));
		sort(all(v2));

		vector<int> test;
		for(int i=0;i<v1.size();i++) {
			test.pb(v1[i]);
			test.pb(v1[i]-1);
			test.pb(v1[i]+1);
		}
		for(int i=0;i<v2.size();i++) {
			test.pb(v2[i]);
			test.pb(v2[i]-1);
			test.pb(v2[i]+1);
		}

		test.pb(a);
		test.pb(a+1);
		test.pb(b);
		test.pb(b-1);

		sort(all(test));

		int mx = -1;
		int ans = -1;

		for(int i=0;i<test.size();i++) {
			if(test[i]<a||test[i]>b) continue;
			int score = 0;

			int l1 = lower_bound(v1.begin(),v1.end(),test[i]) - v1.begin();
			int l2 = lower_bound(v2.begin(),v2.end(),test[i]) - v2.begin();

			int g1 = (int)(v1.end() - upper_bound(v1.begin(),v1.end(),test[i]));
			int g2 = (int)(v2.end() - upper_bound(v2.begin(),v2.end(),test[i]));
			
			score = l1*g2 + l2*g1;
			score *= 3;

			int e1 = (int)v1.size() - l1 - g1;
			int e2 = (int)v2.size() - l2 - g2;

			score += e1*(l2+g2) + e2*(l1+g1);

			assert(e1>=0&&e1<=1);
			assert(e2>=0&&e2<=1);

			if(mx<score) {
				mx = score;
				ans = test[i];
			}
		}

		assert(ans!=-1);
		cout<<ans<<endl;
	}
}