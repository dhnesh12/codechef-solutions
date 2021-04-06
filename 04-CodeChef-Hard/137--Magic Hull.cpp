#include <math.h>
#include <stdio.h>
#include <algorithm>
#define L long long
#define N 155
#define U 1<<22
#define dmax(a,b) ((a)>(b)?(a):(b))
#define dabs(a) ((a)<(0)?(-a):(a))
#define F()((I==J&&(J=(I=B)+fread(B,1,U,stdin),I==J))?0:*I++)
char B[U],*I=B,*J=B;
template<class T>inline void Rin(T &x)
{
	x=0;int c=F();bool b=0;
	for(;c<48||c>57;c=F())
		if(c==45)b=1;
	for(;c>47&&c<58;c=F())
		x=(x<<1)+(x<<3)+c-48;
	x=b?-x:x;
}
struct VV
{
	int x,y;
	VV(int _=0,int __=0)
		{
		x=_;
		y=__;
		}
	bool operator < (VV o) const
		{
		return x<o.x||x==o.x&&y<o.y;
		}
	bool operator == (VV o) const
		{
		return x==o.x&&y==o.y;
		}
	L operator ^ (VV o) const
		{
		return (L)x*o.y-(L)y*o.x;
		}
	VV operator + (VV o) const
		{
		return VV(x+o.x,y+o.y);
		}
	VV operator - () const
		{
		return VV(-x,-y);
		}
	int p()
		{
		return y>0||y==0&&x>0;
		}
}V[N];
struct PP
{
	VV f;
	L s;
	PP(VV _=0,L __=0)
		{
		f=_;
		s=__;
		}
	bool operator < (PP o) const
		{
		return f<o.f||f==o.f&&s<o.s;
		}
	bool operator == (PP o) const
		{
		return f==o.f&&s==o.s;
		}
}P[N*N*N/6];
bool A(VV a,VV b)
{
	int p=a.p();
	int q=b.p();
	if(p!=q)
		{
		return p>q;
		}
	return (a^b)>0;
}
int n,_t,_k;
L ans;
int main()
{
	Rin(n);
	for(int i=0;i<n;i++)
		{
		Rin(V[i].x);
		Rin(V[i].y);
		}
	std::sort(V,V+n,A);
	for(int i=0;i<n;i++)
		{
		for(int j=i;j<n;j++)
			{
			L m=V[i]^V[j];
			if(m<0)
				{
				break;
				}
			m=dabs(m);
			P[_t++]=PP(V[i]+V[j],m);
			for(int k=j;k<n;k++)
				{
				if((V[j]^V[k])<0)
					{
					break;
					}
				VV t=V[i]+V[j]+V[k];
				if((V[i]^t)>=0)
					{
					P[_t++]=PP(t,m+dabs(V[k]^t));
					}
				}
			}
		}
	std::sort(P,P+_t);
	for(int i=0;i<_t;)
		{
		int j=i;
		for(;j<_t&&P[i].f==P[j].f;j++)
			;
		P[_k++]=P[j-1];
		i=j;
		}
	for(int i=0;i<_k;i++)
		{
		VV t=-P[i].f;
		int j=std::lower_bound(P,P+_k,PP(t,-1LL))-P;
		if(j<_k&&P[j].f==t)
			{
			ans=dmax(ans,P[i].s+P[j].s);
			}
		}
	printf("%lld.%lld\n",ans/2,ans%2*5);
	return 0;
}