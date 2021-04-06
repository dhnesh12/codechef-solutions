#include<bits/stdc++.h>
typedef long long int ll;
typedef unsigned long long int ull;
using namespace std;
#define fast ios_base::sync_with_stdio(false);cin.tie(NULL);
#define fre(i,l,r) for(ll i=l;i<=r;i++)
#define fr(i,l,r)  for(ll i=l;i<r;i++)
#define test(t) ll t;cin>>t; while(t--)
#define mod 998244353
#define debug(x) cout<<" x = "<<x
#define vl vector<ll>
char s[10485761];
void solve(){
	int	num=1;
	char x;
// 	scanf("%c",&x);
	while(~scanf("%c",&x)){
		s[num++] = x;
	}
	num--;
	// out
	for(int i=1;i<=num;i++){
		printf("%c",s[i]);
	}
}

int main(){
	int d;
	string str;
	string text;
	cin>>d;
	vector<string> dict;
	while(d--){
		cin>>str;
		dict.push_back(str);
	}
	solve();
}