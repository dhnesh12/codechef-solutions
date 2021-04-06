#include<bits/stdc++.h>

#define fo(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)

using namespace std;

typedef long long LL;
typedef double db;

int get(){
	char ch;
	while(ch=getchar(),(ch<'0'||ch>'9')&&ch!='-');
	if (ch=='-'){
		int s=0;
		while(ch=getchar(),ch>='0'&&ch<='9')s=s*10+ch-'0';
		return -s;
	}
	int s=ch-'0';
	while(ch=getchar(),ch>='0'&&ch<='9')s=s*10+ch-'0';
	return s;
}

const int N = 1e4+5;

int n,k,R;
int f[N],g[N];
int ad[N];

int main(){
	n=get();k=get();R=get();
	int now=0;
	fo(i,2,n){
		now^=1;
		fd(j,i-1,1)f[j]=f[j-1];
		f[0]=now;
		int tmp=f[i-1];
		fd(j,i-1,1)f[j]=f[j-1];
		f[0]=tmp;
		int lst=-1e9;
		fo(j,0,i-1)
		if (f[j]==now)lst=j;
		else if (j-lst<k)f[j]=now;
		fo(j,0,i-1)
		if (f[j]==now)break;
		else if (j+i-lst<k)f[j]=now;
		int d=1ll*(R/2)*(k+1)%i;
		fo(j,0,i-1)g[(j+d)%i]=f[j];
		fo(j,0,i-1)f[j]=g[j];
	}
	fo(i,0,n-1)putchar(f[i]==now?'A':'B');
	putchar('\n');
	return 0;
}
