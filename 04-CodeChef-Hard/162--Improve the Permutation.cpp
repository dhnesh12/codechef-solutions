#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define fo(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define maxn 55
using namespace std;

int a[maxn];

int ans[maxn * maxn * 2];

int T,n;

void work(){
	ans[0]=0;
	scanf("%d",&n);
	fo(i,1,n) scanf("%d",&a[i]);
	fd(i,n,1) {
		int wz=0;
		fo(j,1,n) if (a[j]==i) wz=j;
		while (wz<i) {
			int tmp=wz;
			while (tmp<n && a[tmp+1]==tmp) tmp++;
			if (tmp<i) {
				fd(k,tmp,wz+1) {
					if (a[k]==k || a[k+1]==k+1 || k==n) continue;
					ans[++ans[0]]=k;
					swap(a[k],a[k+1]);
				}
			}
			if (a[wz]!=wz && a[wz+1]!=wz+1 && wz!=n){
				ans[++ans[0]]=wz;
				swap(a[wz],a[wz+1]);
			}
			wz++;
		}
	}
	printf("%d\n",ans[0]);
	fo(i,1,ans[0]) printf("%d ",ans[i]);
	puts("");
}

int main(){
	scanf("%d",&T);
	while (T--) work();
	return 0;
}