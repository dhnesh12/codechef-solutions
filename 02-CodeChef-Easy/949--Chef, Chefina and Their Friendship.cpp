#include<bits/stdc++.h>
#include<set>
#include<map>
#include<bitset>
#define int long long int
#define rep(i,a,b)  for(i=a;i<b;i++)
#define Sort(a)	sort(a.begin(),a.end())
#define rev(a)	reverse(a.begin(),a.end())
#define all(a)	(a).begin(),(a).end()
#define vll vector<int>
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define db double
#define M 1000000007
#define pi 3.1415926535897932384626433832795028841971
#define INF 1e18
#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

#define MAX 10000005

using namespace std;
int min(int a,int b){return a<b?a:b;}
int min(int a,int b,int c){a=min(a,b);a=min(a,c);return a;}
int max(int a,int b){return a>b?a:b;}
int max(int a,int b,int c){a=max(a,b);a=max(a,c);return a;}
int dsum(int n){int ans=0;while(n){ans+=(n%10);n/=10;}return ans;}
int power(int a,int b){int res=1;while(b){if(b&1) res=res*a;a=a*a;b>>=1;}return res;}
int power(int a,int b,int m){if(b==0)	return 1;if(b==1)	return a%m;int res=1;a=a%m;while(b){if(b&1){res=(res*a)%m;}a=((a%m)*(a%m))%m;b>>=1;}return res;}
int Ceil(int a,int b){int res=a/b;if(a%b!=0)	res++;return res;}

template<typename T>istream &operator>>(istream &is, vector<T> &v) { for (T &t : v) is >> t; return is; }
template<typename T>ostream &operator<<(ostream &os, const vector<T> &v) { for (const T &t : v) {os << t <<" ";} os << '\n'; return os; }

int dxx[]={1,1,0,-1,-1,-1,0,1};
int dyy[]={0,1,1,1,0,-1,-1,-1};
int dx[]={1,0,-1,0};
int dy[]={0,1,0,-1};

struct pll{
	int x,y;
};
bool comp(pll a,pll b){
	if(a.x==b.x)	return a.y<b.y;
	else	return a.x<b.x;
}

// cout << fixed << setprecision(10);

void solve(int the)
{
	char ch;
	db aa,bb,cc,dd,xx;
	string s1,s2,s3,str;
    int i,j,k,a,b,c,d,n,m,l,r,x,y,z,low,high,mid,sum=0,ans=0,temp,t;
    cin >> s1;
    n=s1.length();
    int hash[n+1];
    int pr[n+1];
    int p=911382323;
    hash[0]=0;pr[0]=1;
    hash[1]=s1[0]-'a'+1;pr[1]=p;
    rep(i,2,n+1){
        hash[i]=((hash[i-1]*p)+(s1[i-1]-'a'+1))%M;
        pr[i]=(pr[i-1]*p)%M;
    }
    for(int len=1;len<=(n-2)/2;len++){
        int val1,val2,val3,val4;
        l=1;r=len;d=r-l+1;
        val1=(hash[r]-((hash[l-1]*pr[d])%M))%M;
        if(val1<0)  val1+=M,val1%=M;
        l=r+1;r=2*len;d=r-l+1;
        val2=(hash[r]-((hash[l-1]*pr[d])%M))%M;
        if(val2<0)  val2+=M,val2%=M;
        a=n-r;a/=2;
        l=r+1;r=l+a-1;d=r-l+1;
        val3=(hash[r]-((hash[l-1]*pr[d])%M))%M;
        if(val3<0)  val3+=M,val3%=M;
        l=r+1;r=n;d=r-l+1;
        val4=(hash[r]-((hash[l-1]*pr[d])%M))%M;
        if(val4<0)  val4+=M,val4%=M;
        // cout << val1 << " " << val2 << " " << val3 << " " << val4 << endl;
        if((val1==val2) && (val3==val4)){
            ans++;
        }
    }
    cout << ans << endl;
    
    
}















int32_t main()
{
	int t=1,c=1;
	scanf("%lld",&t);
	while(t--){
		solve(c);
		c++;
	}
	return 0;
}
/* UJJWAL KESHRI */
