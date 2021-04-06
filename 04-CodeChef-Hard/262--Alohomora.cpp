#include <bits/stdc++.h>
using namespace std;
#pragma optimize("-O3")
#define int long long int

#define pb push_back
#define endl '\n'
int a[10];
int b[10];
int mini[10][10];



using cd = complex<double>;
const double PI=acos(-1);
int ans[200005];
void fft(vector<cd> & a, bool invert){
	int n=a.size();
	for(int i=1, j=0; i<n; i++){
		int bit=n>>1;
		for(; j&bit; bit>>=1)
			j ^=bit;
		j^=bit;
		if(i<j)
			swap(a[i], a[j]);
	}
	for(int len=2; len<=n; len <<=1){
		double ang=2*PI/len*(invert ? -1 : 1);
		cd wlen(cos(ang), sin(ang));
		for(int i=0; i<n; i+=len){
			cd w(1);
			for(int j=0; j<len/2; j++){
				cd u=a[i+j], v=a[i+j+len/2]*w;
				a[i+j]=u+v;
				a[i+j+len/2]=u-v;
				w*=wlen;
			}
		}
	}
	if(invert){
		for(cd & x : a)
			x /= n;
	}
}
 
vector<int> multiply(vector<int>const& a, vector<int>const& b){
	vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	int n=1;
	while(n<a.size()+b.size())
		n <<= 1;
	fa.resize(n);
	fb.resize(n);
	fft(fa, false);
	fft(fb, false);
	for(int i=0; i<n; i++)
		fa[i] *= fb[i];
	fft(fa, true);
	vector<int>result(n);
	for(int i=0; i<n; i++)
		result[i]=round(fa[i].real());
	return result;
}



main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, m;
	cin>>n>>m;
	string s, t;
	cin>>s>>t;
	
	for(int i=0; i<10; i++){
		cin>>a[i];
	}
	
	for(int i=0; i<10; i++){
		cin>>b[i];
	}
	
	for(int i=0; i<10; i++){
		for(int j=0; j<10; j++){
			mini[i][j]=1e9;
			for(int k=0; k<10; k++){
				int sum=0;
				int val1=i;
				int val2=j;
				while(val1!=k){
					sum+=a[val1];
					val1++;
					val1=val1%10;
				}
				while(val2!=k){
					sum+=b[val2];
					val2++;
					val2=val2%10;
				}
				mini[i][j]=min(mini[i][j], sum);
			}
		}
	}
	
	for(int i=0; i<10; i++){
		vector<int>v1;
		vector<int>v2;
		for(int j=0; j<s.size(); j++){
			int num=s[j]-'0';
			v1.pb(mini[num][i]);
		}
		for(int j=0; j<t.size(); j++){
			int num=t[j]-'0';
			if(num==i){
				v2.pb(1);
			}
			else{
				v2.pb(0);
			}
		}
		reverse(v2.begin(), v2.end());
		vector<int>mul=multiply(v1, v2);
		int pt=0;
		for(int j=t.size()-1; j<s.size(); j++){
			ans[pt]+=mul[j];
			pt++;
		}
	}
	int mini=1e18;
	for(int i=0; i<s.size()-t.size()+1; i++){
		mini=min(mini, ans[i]);
	}
	cout<<mini;
	
	
	return 0;
}