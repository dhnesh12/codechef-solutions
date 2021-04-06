#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define MN 51
#define eps 1e-12l
using namespace std;

int read_p,read_ca;
inline int read(){
    read_p=0;read_ca=getchar();
    while(read_ca<'0'||read_ca>'9') read_ca=getchar();
    while(read_ca>='0'&&read_ca<='9') read_p=read_p*10+read_ca-48,read_ca=getchar();
    return read_p;
}
const double pi=atan(1.0)*4.0/180;
int T,n,l[MN],p[MN],mmh;
double x[MN],y[MN],z[MN],X,Y,Z,t,i,j;
inline double sqr(double x){return x*x;}
inline double dis(double x,double y,double z,double _x,double _y,double _z){return sqrt(sqr(x-_x)+sqr(y-_y)+sqr(z-_z));}
inline void work(double X,double Y,double Z){
	int MMH=0,i;
	for (i=1;i<=n&&MMH<mmh;i++)
	MMH+=dis(x[i],y[i],z[i],X,Y,Z)+eps<dis(-x[i],-y[i],-z[i],X,Y,Z);
	
	if (MMH<mmh) mmh=MMH;
}
inline void cross(int a,int b){X=y[a]*z[b]-z[a]*y[b];Y=z[a]*x[b]-x[a]*z[b];Z=x[a]*y[b]-x[b]*y[a];}
int main(){
	register int i,j;
	T=read();
	while (T--){
		n=read();mmh=1e9;
		for (i=1;i<=n;i++) p[i]=read(),l[i]=read();
		for (t=0;t<360;t+=0.5){
			for (i=1;i<=n;i++)
			x[i]=sin((t+p[i])*pi)*cos(pi*l[i]),
			y[i]=sin((t+p[i])*pi)*sin(pi*l[i]),
			z[i]=cos((t+p[i])*pi);
			
			
			for (i=1;i<=n;i++)
			for (j=1;j<i;j++)
			cross(i,j),work(X,Y,Z);
		}
		printf("%d\n",mmh);
	}
}