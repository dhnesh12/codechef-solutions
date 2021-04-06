//ΔCC FINDSEQ
#include<iostream>
#include<cstdio>
#include<fstream>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<bitset>
#include<cmath>
#include<cstring>
#include<cstdlib>
using namespace std;
typedef long long LL;
typedef double DB;
const int N = 1005;
char ch[11];
map<int,int> M;
map<int,int>::iterator it;
int n,a[N],b[11],c[11],d[11],f[N][N],l1[N][N],l2[N][N],r1[N][N],r2[N][N];
int L,R,fl;
void LR(int o){
	o=b[o];
	L=0,R=n+1;
	for(int i=1;i<=5;i=i+1){
		if(d[i]){
			if(b[i]<o&&a[d[i]]>L)
				L=a[d[i]];
			if(b[i]>o&&a[d[i]]<R)
				R=a[d[i]];
		}
	}
	L++,R--;
}
void L1(){
	LR(1);
	d[1]=l1[d[2]-1][L];
	if(!d[1]||a[d[1]]>R)
		fl=0;
}
void L2(){
	LR(1);
	d[1]=l2[d[2]-1][R];
	if(!d[1]||a[d[1]]<L)
		fl=0;
}
void R1(){
	LR(5);
	d[5]=r1[d[4]+1][L];
	if(!d[5]||a[d[5]]>R)
		fl=0;
}
void R2(){
	LR(5);
	d[5]=r2[d[4]+1][R];
	if(!d[5]||a[d[5]]<L)
		fl=0;
}
int ff(int l,int r,int u,int d){
	if(l>r||u>d)
		return 0;
	l--,u--;
	return f[r][d]+f[l][u]-f[r][u]-f[l][d];
}
int main()
{
	int tc,i,j,o,x,y,z,ans;
	scanf("%d",&tc);
	while(tc--){
		M.clear();
		memset(f,0,sizeof(f));
		memset(l1,0,sizeof(l1));
		memset(l2,0,sizeof(l2));
		memset(r1,0,sizeof(r1));
		memset(r2,0,sizeof(r2));
		/*for(i=1;i<=5;i=i+1)
			ch[i]=i+'0';
		random_shuffle(ch+1,ch+6);
		n=20;
		for(i=1;i<=n;i=i+1)
			a[i]=rand()%n;*/
		scanf("%d%s",&n,ch+1);
		for(i=1;i<=n;i=i+1)
			scanf("%d",a+i),M[a[i]]=1;
		o=0;
		for(it=M.begin();it!=M.end();it++)
			(*it).second=++o;
		for(i=1;i<=n;i=i+1){
			a[i]=M[a[i]];
			for(j=1;j<=n;j=j+1)
				f[i][j]+=f[i-1][j];
			f[i][a[i]]++;
		}
		for(i=1;i<=n;i=i+1)
			for(j=1;j<=n;j=j+1)
				f[i][j]+=f[i][j-1];
		for(i=1;i<=n;i=i+1){
			for(j=1;j<=n;j=j+1)
				l1[i][j]=l1[i-1][j],l2[i][j]=l2[i-1][j];
			for(j=1;j<=a[i];j=j+1)
				if(!l1[i][j]||a[l1[i][j]]>a[i])
					l1[i][j]=i;
			for(j=a[i];j<=n;j=j+1)
				if(!l2[i][j]||a[l2[i][j]]<a[i])
					l2[i][j]=i;
		}
		for(i=n;i;i=i-1){
			for(j=1;j<=n;j=j+1)
				r1[i][j]=r1[i+1][j],r2[i][j]=r2[i+1][j];
			for(j=1;j<=a[i];j=j+1)
				if(!r1[i][j]||a[r1[i][j]]>a[i])
					r1[i][j]=i;
			for(j=a[i];j<=n;j=j+1)
				if(!r2[i][j]||a[r2[i][j]]<a[i])
					r2[i][j]=i;
		}
		for(i=1;i<=5;i=i+1)
			b[i]=ch[i]-'0';
		x=min(b[1],min(b[3],b[5]));
		z=max(b[1],max(b[3],b[5]));
		y=b[1]+b[3]+b[5]-x-z;
		d[0]=0,d[6]=n+1;
		ans=0;
		for(i=1;i<=n;i=i+1){
			for(j=i+1;j<=n;j=j+1){
				if((b[2]>b[4])^(a[i]>a[j]))
					continue;
				fl=1;
				d[1]=0,d[3]=0,d[5]=0;
				d[2]=i,d[4]=j;
				if(b[1]==y){
					if(b[5]==x)
						R1(),L1();
					else
						R2(),L2();
				}
				if(b[1]==x){
					L1();
					if(b[5]==y)
						R1();
					else
						R2();
				}
				if(b[1]==z){
					L2();
					if(b[5]==x)
						R1();
					else
						R2();
				}
				if(!fl)
					continue;
				//cout<<d[1]<<d[2]<<d[4]<<d[5]<<endl;
				LR(3);
				if(ff(i+1,j-1,L,R)){
					for(o=i+1;o<=j-1;o=o+1)
						if(L<=a[o]&&a[o]<=R)
							d[3]=o;
					for(o=1;o<=5;o=o+1)
						printf("%d ",d[o]-1);
					printf("\n");
					/*for(o=1;o<=5;o=o+1)
						printf("%d ",b[o]);
					printf("\n");
					for(o=1;o<=5;o=o+1)
						printf("%d ",a[d[o]]);
					printf("\n");*/
					ans=1;
					break;
				}
			}
			if(ans)
				break;
		}
		if(!ans)
			cout<<-1<<endl;
	}
	return 0;
}