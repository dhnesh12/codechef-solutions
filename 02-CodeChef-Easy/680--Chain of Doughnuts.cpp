#include <bits/stdc++.h>
using namespace std;
typedef long long  ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef set<int> si;
typedef map<int,int> mii;
typedef map<ii,int> miii;
typedef map<char,int> mci;
typedef priority_queue <int> pq_g; //to store data in desecending order
typedef priority_queue <int, vector<int>, greater<int>> pq_s; 
#define pb(x) push_back(x);
#define MOD 1000000007
#define YES cout<<"YES"<<endl;
#define NO cout<<"NO"<<endl;
#define p(str) cout<<str;
#define pe(str) cout<<str<<"\n";
#define f(s,n,i) for(i=s;i<n;i++)
#define endl "\n"
#define vl(d)  (int)str[d]-48
#define fast ios_base::sync_with_stdio(false),cin.tie(NULL)

int gcd(ll a,ll b){return (b==0?a:gcd(b,a%b)) ;}

int main()
{ 
  fast;
  int T=1;
  cin>>T;
   while(T--)
   {
    int N,M,Q,K,i,j,k=1,x,y,z,ind,sum=0,flag=1,count=0,mx=0,r=0,a,   
    b,c,mn=INT_MAX,one=0;  
    cin>>N>>M; int arr[M];
    f(0,M,i){
        cin>>arr[i];
        if(arr[i]==1)one++;
    }
    sort(arr,arr+M);
    if(one==M)cout<<one/2<<endl;
    else{
        i=0; j=M-1;
        while(i+1<j){
           x=j-arr[i];
        //   cout<<i<<" "<<j<<" "<<x<<endl;
           if(x<i+1){sum=sum+j-i; break; }
           sum+=arr[i];
           j-=arr[i];
           i++;
       }
       if(M==2)sum=1;
       cout<<sum<<endl;
    }
   } 
 return 0;
}
