#include <set>
#include <map>
#include <cmath>
#include <ctime>
#include <bitset>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <algorithm>
#define PR pair
#define fi first
#define se second
#define mk make_pair
#define pb push_back
#define For(i,x,y)   for(int i=(int)(x);i<=(int)(y);i++)
#define Rep(i,x,y)   for(int i=(int)(x);i< (int)(y);i++)
#define Forn(i,x,y)  for(int i=(int)(x);i>=(int)(y);i--)
#define CH	         ch=getchar()
#define Exit(...)    printf(__VA_ARGS__),exit(0)
#define dln()        fprintf(stderr,"\n")
#define dprintf(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
typedef double	  db;
typedef long long ll;
typedef PR<int,int> PII;
const	int inf=1e9;
const	ll Inf=1e10;
const	int P=1e9+7;
const	int N=100005;

inline int IN(){
	int x=0;int ch=0,f=0;
	for(CH;ch!=-1&&(ch<48||ch>57);CH)  f=(ch=='-');
	for(;ch>=48&&ch<=57;CH) x=(x<<1)+(x<<3)+ch-'0';
	return f?(-x):x;
}

int Pow(int x,int y,int p){
	int a=1;
	for(;y;y>>=1,x=(ll)x*x%p) if(y&1) a=(ll)a*x%p;
	return a;
}

int S=71;
int a[105]={0,272,589185,930336768,853401154,217676188,136558333,415722813,985269529,791527976,201836136,382110354,441223705,661537677,641601343,897033284,816519670,365311407,300643484,936803543,681929467,462484986,13900203,657627114,96637209,577140657,600647073,254604056,102389682,811580173,592550067,587171680,526467503,265885773,951722780,219627841,371508152,283501391,159234514,439380999,722868959,125599834,351398134,456317548,365496182,614778702,502680047,193063685,309004764,743901785,870955115,312807829,160375015,691844624,137034372,350330868,895680450,282610535,317897557,28600551,583305647,539409363,327406961,627805385,680183978,681299085,954964592,743524009,788048339,699454626,666369521,857206425};
int v[105]={0,1,999998256,116405,85452673,554115042,156014244,348050269,827145587,499362222,235020451,945246280,487523377,181812482,999805738,781667749,156019930,487004069,165048565,223916257,568547436,266083964,165436872,706679916,38928432,777681484,775353772,209550973,934884057,649159321,726116404,38175356,256245988,152683562,899906518,82346955,244730388,755269619,917653052,100093489,847316445,743754019,961824651,273883603,350840686,65115950,790449034,224646235,222318523,961071575,293320091,834563135,733916043,431452571,776083750,834951442,512995938,843980077,218332258,194269,818187525,512476630,54753727,764979556,500637785,172854420,651949738,843985763,445884965,914547334,999883602,1751};

struct mat{
	int v[105][105];
}c,e[105],tmp;

mat operator *(const mat &a,const mat &b){
	For(i,1,S) For(j,1,S){
		c.v[i][j]=0;
		For(k,1,S) c.v[i][j]=(c.v[i][j]+1ll*a.v[i][k]*b.v[k][j])%P;
	} return c;
}

int an[N],cao[N];
void Pow(int n){
	For(i,1,71) an[i]=a[72-i];
	For(x,0,30)if((n>>x)&1){
		For(i,1,71) cao[i]=an[i];
		For(i,1,71){
			an[i]=0;
			For(j,1,71){
				an[i]=(an[i]+1ll*cao[j]*e[x].v[j][i])%P;
			}
		}
	}
}

int main(){
/*
	For(i,72,73){
		For(j,1,S) a[i]=(a[i]+1ll*a[i-j]*v[S-j+1])%P;
		dprintf("%d\n",a[i]);
	}
	return 0;
*/
	For(i,2,S) e[0].v[i-1][i]=1;
	For(i,1,S) e[0].v[i][1]=v[S-i+1];
	For(i,1,30) e[i]=e[i-1]*e[i-1];
	int T=IN();
	while(T--){
		int n=IN();
		if(n<=S) printf("%d\n",a[n]);
		else{
			Pow(n-71);
			printf("%d\n",an[1]);
		}
	}
	return 0;
}


