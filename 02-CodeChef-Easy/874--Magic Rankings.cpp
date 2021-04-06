#include<bits/stdc++.h>
#include<string>
using namespace std;
//functions like ceil() and floor() are used to truncate the decimal values
//countsort is great

#define endl "\n"
#define ll long long 
#define int long long 
#define vi vector<int>
#define vlli vector<ll>
#define pii pair<int,int>
#define pb push_back
#define mpr make_pair
#define ft first
#define sec second
#define f0r(n) for(int i=0;i<n;i++)
#define f1r(n) for(int j=0;j<n;j++)
#define rep(i,a,b) for(int i=a;i<b;i++)
#define fastio(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define txtinp(); freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
#define f0rt(n,start,t) for(int i=start;i<n;i+=t)
#define f1rt(n,start,t) for(int j=start;j<n;j+=t)
#define f0R(start) for(int j=start;j>=0;j--)
#define inparr(n); for(int i=0;i<n;i++){cin>>arr[i];}
#define inp(n,arr); for(int i=0;i<n;i++){cin>>arr[i];}
#define inparr2d(n,m) for(int i=0;i<n;i++){for(int j=0;j<m;j++){cin>>arr[i][j];}}
#define inp2d(n,m,arr) for(int i=0;i<n;i++){for(int j=0;j<m;j++){cin>>arr[i][j];}}
#define out(arr); for(int i=0;i<arr.size();i++){cout<<arr[i]<<" " ;}cout<<endl;
#define srtarr(); sort(arr.begin(),arr.end());
#define srt(arr); sort(arr.begin(),arr.end());
#define rsrt(arr); sort(arr.rbegin(),arr.rend());
#define all(k) k.begin(),k.end()
#define allr(k) k.rbegin(),k.rend()

signed main(){
	fastio();
	// txtinp();
	int testc=1;cin>>testc;
	while(testc--){
		int n;cin>>n;
		int arr[n][n];

		f0r(n){
			f1r(n){
				cin>>arr[i][j];
			}
		}

		double ans = 0;
		int grid[n][n];
		f0r(n){
			f1r(n){
				grid[i][j] = 0;//<<" ";
			}//cout<<endl;
		}
		grid[n-1][n-1] = 0;
		int sum = 0;
		for(int i=n-2;i>=0;i--){
			sum += arr[n-1][i];
			grid[n-1][i] = sum;
		}sum = 0;
		for(int i=n-2;i>=0;i--){
			sum += arr[i][n-1];
			grid[i][n-1] = sum;
		}

		for(int i = n-2;i>=0;i--){
			for(int j = n-2;j>=0;j--){
				int a = grid[i+1][j];
				int b = grid[i][j+1];

				grid[i][j] = arr[i][j] + max(a,b);
			}
		}
		if(grid[0][0] < 0)
			cout<<"Bad Judges\n";
		else
			cout<<fixed<<setprecision(6)<<(double)grid[0][0]/(2*n-3)<<endl;

	}
	cerr << "Time : " << 1000 * ((double)clock()) / (double)CLOCKS_PER_SEC << "ms\n";
	return 0;
}

