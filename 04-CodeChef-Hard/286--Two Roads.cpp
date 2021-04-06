#include<bits/stdc++.h>
#define R register
#define inline __inline__ __attribute__((always_inline))
#define fp(i,a,b) for(R int i=(a),I=(b)+1;i<I;++i)
template<class T>inline bool cmin(T&a,const T&b){return a>b?a=b,1:0;}
using namespace std;
const int N=105;const double eps=1e-10;
struct node
{
    double x,y;
    inline node(){}
    inline node(R double xx,R double yy):x(xx),y(yy){}
    inline node operator +(const node &b)const{return node(x+b.x,y+b.y);}
    inline node operator -(const node &b)const{return node(x-b.x,y-b.y);}
    inline double operator *(const node &b)const{return x*b.y-y*b.x;}
    inline node operator *(const double &b)const{return node(x*b,y*b);}
    inline double operator ^(const node &b)const{return x*b.x+y*b.y;}
}p[N],v;
struct qwq
{
    node p;double d;bool in;
    inline qwq(){}
    inline qwq(R node pp,R double dd,R bool ii):p(pp),d(dd),in(ii){}
    inline bool operator <(const qwq &b)const{return d<b.d;}
}st[N];
struct Line
{
    double x,y,xx,yy,xy;int sz;
    inline void ins(R node p){x+=p.x,y+=p.y,xx+=p.x*p.x,yy+=p.y*p.y,xy+=p.x*p.y,++sz;};
    inline void del(R node p){x-=p.x,y-=p.y,xx-=p.x*p.x,yy-=p.y*p.y,xy-=p.x*p.y,--sz;};
    inline void clr(){x=y=xx=yy=xy=sz=0;}
    double calc()
    {
        if(!sz)return 0;
        double xa=x/sz,ya=y/sz,A=xx-sz*xa*xa;
        double B=2*xa*ya*sz-2*xy,C=yy-sz*ya*ya;
        double a=4,b=-4*(A+C),c=4*A*C-B*B;
        return (-b-sqrt(b*b-4*a*c))/(a*2);
    }
}l1,l2;
double res=1e18;int n;
int main()
{
    scanf("%d", &n);
    fp(i, 1, n)
        scanf("%lf%lf", &p[i].x, &p[i].y);
    fp(a, 1, n)
        fp(b, 1, n)
            if (a != b)
            {
                v = p[b] - p[a];
                fp(i, 1, n)
                    st[i] = qwq(p[i], v ^ (p[i] - p[a]), v * (p[i] - p[a]) > eps);
                st[a].in = 1;
                sort(st + 1, st + 1 + n);
                l1.clr();
                l2.clr();
                fp(i, 1, n)st[i].in ? l1.ins(st[i].p) : l2.ins(st[i].p);
                cmin(res, l1.calc() + l2.calc());
                fp(i, 1, n)
                {
                    if (st[i].in)
                        l1.del(st[i].p), l2.ins(st[i].p);
                    else
                        l2.del(st[i].p), l1.ins(st[i].p);
                    cmin(res, l1.calc() + l2.calc());
                }
            }
    printf("%.10lf\n", res / n);
}