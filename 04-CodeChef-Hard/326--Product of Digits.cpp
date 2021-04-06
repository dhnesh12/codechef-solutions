/*
题意中要求的数每个位上的数为0~9
而0只在p=0时的情况出现,特判
所以每个位上的数可以分解为2^a * 3^b * 5^c * 7^d
(因为1~9中最大的质因数为7)
而我们尽量要取 能被尽量多的质因子乘起来的数,这样肯定最优
(如8 优于 222)
而 2^3=8,3^2=9,5^1=5,7^1=7
所以原题可以变幻成
在a/3+b/2+c+d<700(先只算8,9,5,7,这样最小)的情况下
(题目已经保证位数<700)
2^a*3^b*5^c*7^d≡P(mod 1e9+7)
我们可以考虑折半搜索
原式可变形为
2^a*3^b≡P/(5^c*7^d)(mod 1e9+7)
所以我们只要算左半边的集合
{2^a*3^b<(a/3+b/2<700)}
//括号里的是当最优情况时的粗略的最小位数
再算出右半边的集合
{P/(5^c*7^d)(c+d<700)}
求交集(相等即可),若有多个,算后取最小
然后从9到2取即可
*/
#include<bits/stdc++.h>
#define int long long
#define fir first
#define sec second
using namespace std;
const int mod=1e9+7,inf=700;
const int N=3e3;
int T;
int p,p5,p7,Inv5,Inv7;
int minn;
int ans2,ans3,ans5,ans7;
int p2[N],p3[N],inv5[N],inv7[N];
int w2,w3,w4,w5,w6,w7,w8,w9;
unordered_map<int,pair<int,int> >m;
int power(int x,int y)
{
	int sum=1;
	while(y)
	{
		if(y&1)sum=(sum*x)%mod;
		y>>=1;
		x=x*x%mod;
	}
	return sum;
}
void pre()
{
	Inv5=power(5,mod-2),Inv7=power(7,mod-2);
	p2[0]=p3[0]=inv5[0]=inv7[0]=1;
	for(int i=1;i<=2200;i++)
	{
		p2[i]=1ll*p2[i-1]*2%mod;
		p3[i]=1ll*p3[i-1]*3%mod;
		inv5[i]=1ll*inv5[i-1]*Inv5%mod;
		inv7[i]=1ll*inv7[i-1]*Inv7%mod;
//		printf("%lld %lld %lld\n",p2[0],p3[0],p2[0]*p3[0]);
	}
//	cout<<p2[0]*p3[0]<<endl;
	for(int i=0;i<=inf*3;i++)
		for(int j=0;(j<=inf*2)&&(i/3+j/2<=700);j++)
		{
		//	puts("1");
			m[(p2[i]*p3[j]%mod)]=make_pair(i,j);
		}
}
int calc(int x2,int x3,int x5,int x7)
{
	w9=x3/2,w8=x2/3,w5=x5,w7=x7;
	x2%=3,x3%=2;
	w6=0;
	while(x2>=1&&x3>=1)w6++,x2--,x3--;
	w4=x2/2,x2%=2;
	w3=x3,w2=x2;
	return w2+w3+w4+w5+w6+w7+w8+w9;
}
void print(int x,int y)
{
	for(int i=1;i<=x;i++)
		printf("%d",y);
}
signed main()
{
	pre();
	scanf("%lld",&T);
//	cout<<calc(1000,1000,500,500)<<endl;
	while(T--)
	{
		minn=1e9+7;
		ans2=ans3=ans5=ans7=0;
		scanf("%lld",&p);
		if(p==0)
		{
			puts("10");
			continue;
		}
		if(p==1)
		{
			puts("1");
			continue;
		}
		for(int i=0;i<=inf;i++)
			for(int j=0;j<=inf&&i+j<=700;j++)
			{
				int temp=inv5[i]*inv7[j]%mod*p%mod;
				if(m.count(temp))
				{
					int len=calc(m[temp].fir,m[temp].sec,i,j);
					if(len<minn)
					{
						minn=len;
						ans2=m[temp].fir,ans3=m[temp].sec;
						ans5=i,ans7=j;
					}
				}
			}
		calc(ans2,ans3,ans5,ans7);
		print(w2,2);print(w3,3);print(w4,4);print(w5,5);
		print(w6,6);print(w7,7);print(w8,8);print(w9,9);
		puts("");
	}
}