#include<cmath>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cctype>
#include<fstream>
#include<string>
#include<vector>
#include<queue>
#include<map>
#include<set>
#include<sstream>
#include<stack>
#include<stdlib.h>
#include<iostream>
#include<algorithm>

#define sc1(a) scanf("%d",&a)
#define sc2(a,b) scanf("%d %d",&a,&b)
#define sc3(a,b,c) scanf("%d %d %d",&a,&b,&c)
#define scd1(a) scanf("%lf",&a)
#define scd2(a,b) scanf("%lf %lf",&a,&b)
#define scd3(a,b,c) scanf("%lf %lf %lf",&a,&b,&c)
#define scl1(a) scanf("%lld",&a)
#define scl2(a,b) scanf("%lld %lld",&a,&b)
#define scl3(a,b,c) scanf("%lld %lld %lld",&a,&b,&c)

#define cl(vctr) vctr.clear()
#define ms(v, ar) memset(ar, v, sizeof(ar))

const double pi=(double)(2.0 * acos( 0.0 ));
const int inf=1 << 30;
const double eps=1E-9;
const double e = exp(1.0);
const int sz=100000 + 5;

using namespace std;
typedef long long int ll;
const ll mod=1000000000 + 7;

int sqr_rt[2000005];
vector<int> pxb, pxc, pyb, pyc;

void store_all_pt(vector<int> &x, vector<int> &y, int side)
{
    for(int i=0; i*i <= side; i++)
        if(sqr_rt[side - i*i] != -1) {
            int j=sqr_rt[side - i*i];
            x.push_back(i), y.push_back(j);
            x.push_back(-i), y.push_back(j);
            x.push_back(-i), y.push_back(-j);
            x.push_back(i), y.push_back(-j);
        }
}

void bring_at_org(int &xa, int &ya, int &xb, int &yb, int &xc, int &yc)
{
    if(xb<0) {
        xb = -xb;
        xa += xb;
        xc += xb;
        xb = 0;
    }

    if(yb<0) {
        yb = -yb;
        ya += yb;
        yc += yb;
        yb = 0;
    }

    if(xc<0) {
        xc = -xc;
        xa += xc;
        xb += xc;
        xc = 0;
    }

    if(yc<0) {
        yc = -yc;
        ya += yc;
        yb += yc;
        yc = 0;
    }
}

int give_cnt(int m, int xa, int ya, int xb, int yb, int xc, int yc)
{
    int mxx = max(xa, max(xb, xc));
    int mxy = max(ya, max(yb, yc));
    return (m - mxx + 1)*(m - mxy + 1);
}

int main()
{
	int t,T;

    ms(-1, sqr_rt);
	for(int side=0; side * side < 2000005; side ++)
        sqr_rt[side * side] = side;

	sc1(t);
	T=t;
	while(t--)
	{
		int m,k;
		sc2(m,k);
		printf("Case #%d:\n", T-t);
		for(int k1=0;k1<k;k1++)
		{
		    int xa, ya, xb, yb, xc, yc;
            sc2(xa, ya);
            sc2(xb, yb);
            sc2(xc, yc);

            xb -= xa, yb -= ya;
            xc -= xa, yc -= ya;
            xa = ya = 0;

            int ab2 = xb*xb + yb*yb;
            int ac2 = xc*xc + yc*yc;
            int bc2 = (xb - xc)*(xb - xc) + (yb - yc)*(yb - yc);

            pxb.clear();
            pyb.clear();
            pxc.clear();
            pyc.clear();

            store_all_pt(pxb, pyb, ab2);
            store_all_pt(pxc, pyc, ac2);

            int b = pxb.size(), c = pxc.size();

            ll res = 0;
            set< vector< pair<int, int> > > all_abc;

            for(int i=0; i<b; i++)
                for(int j=0; j<c; j++) {
                    xa=ya=0;
                    xb=pxb[i], yb=pyb[i];
                    xc=pxc[j], yc=pyc[j];

                    if((xb - xc)*(xb - xc) + (yb - yc)*(yb - yc) != bc2) continue;

                    bring_at_org(xa, ya, xb, yb, xc, yc);

                    if(xa>m || xb>m || xc>m || ya>m || yb>m || yc>m) continue;

                    vector< pair<int, int> > abc;
                    abc.push_back(make_pair(xa, ya));
                    abc.push_back(make_pair(xb, yb));
                    abc.push_back(make_pair(xc, yc));

                    sort(abc.begin(), abc.end());

                    if(all_abc.find(abc) != all_abc.end()) continue;

                    all_abc.insert(abc);

                    res += (ll)give_cnt(m, xa, ya, xb, yb, xc, yc);
                }
            printf("%lld\n", res);
		}
		printf("\n");
	}

    return 0;
}
