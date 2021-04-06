#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline char getch(){
	static char buf[10000],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
#define Getc getch
inline ll read(){
	ll s=0,f=1;char ch=Getc();
	while(ch<'0'||ch>'9')f=(ch=='-'?-1:1),ch=Getc();
	while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=Getc();
	return s*f;
}
#define filename "bear"
void File(){
	freopen(filename".in","r",stdin);
	freopen(filename".out","w",stdout);
}
const int MaxN=300+5;
int n,m,K,d[MaxN][MaxN];
int a[MaxN][MaxN];
char s[MaxN];
int Ask(int x1,int y1,int x2,int y2){
	return a[x2][y2]-a[x1-1][y2]-a[x2][y1-1]+a[x1-1][y1-1];
}
void Add(int x1,int y1,int x2,int y2){
	if(y1>y2||x1>x2)return;
	d[x1][y1]++;d[x1][y2+1]--;d[x2+1][y1]--;d[x2+1][y2+1]++;
}
bool check(int x1,int y1,int x2,int y2){
	return Ask(x1,y1,x2,y2)>=K;
}
int main(){
//	File();
	scanf("%d%d%d",&n,&m,&K);
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=m;j++)a[i][j]=(s[j]=='H');
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)
	a[i][j]=a[i][j]+a[i-1][j]+a[i][j-1]-a[i-1][j-1];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int p=m+1,lst=m;
			for(int k=i;k<=n;k++){
				while(p-1>=j&&check(i,j,k,p-1))p--;
				if(p>m||p>lst)continue;
				Add(k-i+1,p-j+1,n-i+1,lst-j+1);
				lst=p-1;
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)
		d[i][j]=d[i][j]+d[i-1][j]+d[i][j-1]-d[i-1][j-1];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)
		d[i][j]=d[i][j]+d[i-1][j]+d[i][j-1]-d[i-1][j-1];
	}
	int Q;scanf("%d",&Q);
	while(Q--){
		int A,B;
		scanf("%d%d",&A,&B);
		printf("%d\n",d[A][B]);
	}
	return 0;
}
/*
5 5 4
H.H..
..H..
H...H
HHHH.
HH..H
2
1 1
2 3
*/