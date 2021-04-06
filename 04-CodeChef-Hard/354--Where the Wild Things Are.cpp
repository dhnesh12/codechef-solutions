#include<stdio.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define MaxN 60005
double EPS = 1e-12;

struct PT { 
	double x, y; 
	PT(double a=0, double b=0){
		x=a;y=b;
	}
	PT operator + (const PT &p)  const { return PT(x+p.x, y+p.y); }
	PT operator - (const PT &p)  const { return PT(x-p.x, y-p.y); }
	PT operator * (double c)     const { return PT(x*c,   y*c  ); }
	PT operator / (double c)     const { return PT(x/c,   y/c  ); }
}in[2*MaxN];
double dot(PT p,PT q){
	return p.x*q.x + p.y*q.y;
}
double dist2(PT p,PT q){
	return dot(p-q,p-q);
}
double cross(PT p,PT q){
	return p.x*q.y - p.y*q.x;
}
double area(PT a,PT b,PT c)
{
//	printf("%lf %lf %lf %lf %lf %lf\n",a.x,a.y,b.x,b.y,c.x,c.y);
	return fabs(cross(a-b,a-c))/(double)2;
}
int ternary(int b,int c,int low,int high)
{
	if(high-low<=1){
		double a1 = area(in[b],in[c],in[low]),a2 = area(in[b],in[c],in[high]);	
		if(a1>a2)	return low;
		else	return high;
	}
	int l=(high+2*low)/3,h=(low+2*high)/3;
	double a1 = area(in[b],in[c],in[l]),a2 = area(in[b],in[c],in[h]);
	if(a1>a2){
		return ternary(b,c,low,h-1);
	}
	else	return ternary(b,c, l+1,high);
}
int bs(int b,int c,int low,int high,double S)
{
	if(high<low)	return low;
	if(area(in[b],in[c],in[low])>=S)	return low-1;
	int mid = (low+high)/2;
	if(area(in[b],in[c],in[mid])>=S)	return bs(b,c,low,mid-1,S);
	if(area(in[b],in[c],in[mid])<S && area(in[b],in[c],in[mid+1])>=S)	return mid;
	if(area(in[b],in[c],in[mid])<S)	return bs(b,c,mid+1,high,S);
}
int bs1(int b,int c,int low,int high,double S)
{
        if(high<low)    return low;
	if(area(in[b],in[c],in[high])>=S)        return high+1;
        int mid = (low+high)/2;
        if(area(in[b],in[c],in[mid])>=S)        return bs1(b,c,mid+1,high,S);
        if(area(in[b],in[c],in[mid])<S && area(in[b],in[c],in[mid-1])>=S)       return mid;
        if(area(in[b],in[c],in[mid])<S) return bs1(b,c,low,mid-1,S);
}
void check_area()
{
	int T,a,b,c;
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%d",&a,&b,&c);
		printf("%lf\n",area(in[a],in[b],in[c]));
	}
}
int main()
{
	double S;
	int N,Q,b,c;
	scanf("%d%d",&N,&Q);
	for(int i=1;i<=N;i++){
		scanf("%lf%lf",&in[i].x,&in[i].y);
		in[i+N] = in[i];
	}
	//check_area();
	while(Q--){
		scanf("%d%d%lf",&b,&c,&S);
		if(b>c)	swap(b,c);
		int ind1 = ternary(b,c,b+1,c-1);
		int ind2 = ternary(b,c,c+1,b+N-1);
		//printf("%d is ind1 and %d is ind2\n",ind1,ind2);
		int answer = 0;
		if(area(in[b],in[c],in[ind1])>=S){
			int t1 = bs(b,c,b+1,ind1,S);
			int t2 = bs1(b,c,ind1+1,c-1,S);
			//printf("%d is t1 and %d is t2\n",t1,t2);
			answer += ind1-t1 + t2 -(ind1+1) ; 
		}
		if(area(in[b],in[c],in[ind2])>=S)
			answer += ind2-bs(b,c,c+1,ind2,S) + bs1(b,c,ind2+1,b+N-1,S)-(ind2+1);
		printf("%d\n",answer);
	}
	return 0;
}
