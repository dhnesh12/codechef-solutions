#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef long int ld;
typedef pair<ll,int> pli;
#ifndef local
	//#define endl '\n'
#endif
#define fi first
#define se second
#define pb push_back
#define empb emplace_back
#define all(x) (x).begin(), (x).end()
#define mem(x) memset(x,0,sizeof(x))
#define lowbit(x) ((x)&(-x))
#define caze(QAQ) for(cin>>QAQ;QAQ--;)
int n,A,B;
int ask(int x)
{
	int v1,v2;
	cout<<"1 "<<(A=x)<<endl;
	cin>>v1;
	cout<<"1 "<<(B=x+n/2)<<endl;
	cin>>v2;
	return v1-v2;
}
void ans(){cout<<"2 "<<A<<' '<<B<<endl;}
int main()
{
	cin>>n;
	int sgn=ask(1);
	if(abs(sgn)<=1) ans();
	else
	{
		bool f=sgn>0;
		int L=2,R=n/2-1,mid;
		while(R>=L)
		{
			mid=(L+R)>>1;
			int tp=ask(mid);
			if(abs(tp)<=1) {ans();break;}
			if(f^(tp>0)) R=mid-1;
			else L=mid+1;
		}
	}
}