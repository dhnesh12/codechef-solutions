#include<cstdio>
#include<algorithm>
#include<cstring>
#include<deque>
#define fe first
#define se second
 
using namespace std;
 
typedef pair<int,int> P;
 
deque<P> Hi,Lo;
int C[30005],N,S;
 
double sqr(double a) {return a * a;}
 
double Cross(P a,P b,P c)
{
	return ((c.se - a.se) * (b.fe - a.fe) - (c.fe - a.fe) * (b.se - a.se));
}
 
double Calc(P a,P b)
{
	return sqr(b.se - a.se) / (double)(b.fe - a.fe);
}
 
void read(int &x)
{
	char c;
	while (c = getchar(),c <'0' || c >'9');
	x = c - 48;
	while (c = getchar(),c >= '0' && c <= '9') x = x * 10 + c - 48;
}
 
void Work()
{
	Hi.clear(),Lo.clear();
	read(N),read(S);
	for(int i = 1;i <= N;i ++) read(C[i]),C[i] += C[i - 1];
	Hi.push_back(P(0,0)),Lo.push_back(P(0,0));
	double Ans = 0;
	for(int i = 1;i <= N;i ++)
	{
		P N_1 = P(i,C[i]),N_2 = P(i,C[i] + S);
		while ((Hi.size() > 1) && (Cross(Hi[Hi.size() - 2],N_2,Hi[Hi.size() - 1]) >= 0)) Hi.pop_back();
		while ((Lo.size() > 1) && (Cross(Lo[Lo.size() - 2],N_1,Lo[Lo.size() - 1]) <= 0)) Lo.pop_back();
		if (Hi.size() == 1)
		{
			while ((Lo.size() > 1) && Cross(N_2,Lo[1],Lo[0]) >= 0)
			{
				Ans += Calc(Lo[0],Lo[1]),Lo.pop_front();
				Hi[0] = Lo[0];
			}
		}
		if (Lo.size() == 1)
		{
			while ((Hi.size() > 1) && Cross(N_1,Hi[1],Hi[0]) <= 0)
			{
				Ans += Calc(Hi[0],Hi[1]),Hi.pop_front();
				Lo[0] = Hi[0];
			}
		}
		Hi.push_back(N_2),Lo.push_back(N_1);
	}
	while (Lo.size() > 1) Ans += Calc(Lo[0],Lo[1]),Lo.pop_front();
	printf("%.5f\n", Ans / C[N]);
}
 
int main()
{
	int T;read(T);
	for(;T;T --) Work();
	return 0;
} 