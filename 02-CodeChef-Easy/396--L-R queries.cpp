#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
const int S=1300;
int a[N], l, r;
int bk[N], st[S], en[S];
vector<int>b[N/S+1];
void best(long long &y,int x,vector<int>&v){
	vector<int>::iterator it, jt;
	tie(it,jt)=equal_range(v.begin(),v.end(),x);
	if(jt!=v.begin()) --jt;
	if(it!=v.end())
		y=max(y,1ll*(*it-a[l])*(a[r]-*it));
	if(jt!=v.end())
		y=max(y,1ll*(*jt-a[l])*(a[r]-*jt));
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int n, q;
		scanf("%d %d",&n,&q);
		for(int i=0;i<n;++i)
			scanf("%d",a+i);
		int k=0;
		for(int i=0,j;i<n;i=j){
			st[k]=i;
			auto &v=b[k]; v={};
			for(j=i;j<min(i+S,n);++j){
				bk[j]=k;
				v.emplace_back(a[j]);
			}
			sort(v.begin(),v.end());
			en[k]=j-1;
			++k;
		}
		int qt;
		while(q--){
			scanf("%d %d %d",&qt,&l,&r); --l;
			if(qt==2){
				auto &v=b[bk[l]];
				int i=lower_bound(v.begin(),v.end(),a[l])-v.begin();
				v[i]=r;
				for(int j=i-1;j>=0;--j) if(v[j+1]<v[j]) swap(v[j],v[j+1]);
				for(int j=i+1;j<v.size();++j) if(v[j-1]>v[j]) swap(v[j],v[j-1]);
				a[l]=r;
			}else{
				--r;
				int x=(a[l]+a[r])/2;
				int z=(a[l]+a[r]+1)/2;
				long long y=0;
				for(int i=bk[l];i<=bk[r];++i){
					if(st[i]>=l and en[i]<=r){
						auto &v=b[i];
						best(y,x,v);
						if(z!=x) best(y,z,v);
					}else{
						for(int j=max(st[i],l);j<=min(en[i],r);++j){
							y=max(y,1ll*(a[j]-a[l])*(a[r]-a[j]));
						}
					}
				}
				printf("%lld\n",y);
			}
		}
	}
	return 0;
}