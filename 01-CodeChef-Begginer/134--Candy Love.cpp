#include <iostream>
using namespace std;
#include <climits>
#include <algorithm>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
#define ll long int
#define f(i,j,k) for(i=j;i<k;i++)
#define test_case ll t; scanf("%ld",&t); while(t--)
#define scanl(a,n) ll a[n]; for(i=0;i<n;i++) scanf("%ld",&a[i])
#define printl(a,n) for(i=0;i<n;i++) printf("%ld ",a[i])
#define assign_z(a,n) ll a[n];for(i=0;i<n;i++) a[i]=0
#define input(n) ll n; scanf("%ld",&n)
#define inpstr(a,n) ll n; scanf("%ld",&n);getchar();char a[n+1];gets(a)

int main(){int i,j,k;test_case{ll sum=0;cin>>i;f(j,0,i){cin>>k;sum+=k;}if(sum%2) cout<<"YES"<<endl;else cout<<"NO"<<endl;}return 0;}