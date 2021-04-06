#include <algorithm>
#include <cmath>
#include <cstdio>

using namespace std;

#define R 156

double r[10002];
double p[10002][3];
double z[R];

int main()
{
    //freopen("data.txt", "r", stdin);

    int a, b, n;
    scanf("%d %d %d", &a, &b, &n);

    for (int i=0; i<n; i++)
        scanf("%lf", r+i);

    double ha = a/2., disc, hb = b/2.;
    short inx;
    int A = 100*a;
    int B = 100*b;

    p[0][0] = p[0][1] = p[0][2] = r[0];
    printf("%lf %lf %lf\n", p[0][0], p[0][1], p[0][2]);

    for (short i=1; i<n; i++)
    {
        double x[R] = {r[i]+.000001, a-r[i]-.000001, a-r[i]-.000001,  r[i]+.000001,   ha,  max(ha/2.+.000001, r[i]+.000001),   min(a-ha/2.-.000001, a-r[i]-.000001),    min(a-ha/2.-.000001, a-r[i]-.000001),     max(r[i]+.000001, ha/2.+.000001),          ha,       a-r[i]-.000001,        ha,     r[i]+.000001,          ha,             min(ha+ha/2, a-r[i]-.000001),           ha,                     max(ha-ha/2, r[i]+.000001)};
        double y[R] = {r[i]+.000001,  r[i]+.000001,  b-r[i]-.000001,  b-r[i]-.000001, hb,  max(hb/2.+.000001, r[i]+.000001),   max(hb/2.+.000001, r[i]+.000001),        min(b-hb/2.-.000001, b-r[i]-.000001),     min(b-hb/2.-.000001, b-r[i]-.000001),    r[i]+.000001,        hb,        b-r[i]-.000001,   hb,     max(hb-hb/2, r[i]+.000001),      hb,                   min(hb+hb/2, b-r[i]-.000001),                hb};

        fill(z, z+R, 0);
        //srand((unsigned)time(0));
        for (short k=17; k<R; k++)
        {
            back1:

            x[k] = (rand()%A)/100.;

            if (r[i]+.000001>x[k] || x[k]>a-r[i]-.000001) goto back1;

            back2:

            y[k] = (rand()%B)/100.;

            if (y[k]<r[i]+.000001 || y[k]>b-r[i]-.000001)
                goto back2;
        }

        short stop = i-R+122;
        for (short j = i-1; j>=stop; j--)
            for (short k=0; k<R; k++)
            {
                disc = (r[i]+r[j])*(r[i]+r[j]) - (x[k]-p[j][0])*(x[k]-p[j][0]) - (y[k]-p[j][1])*(y[k]-p[j][1]);

                if (disc < 0)
                    disc = r[i];
                else
                {
                    disc = sqrt(disc);
                    disc += p[j][2]+.000001;
                }

                if (disc > z[k])
                    z[k] = disc;
            }

        inx = 0;
        for (short k=1; k<R; k++)
            if (z[inx]>z[k])
                inx = k;

        p[i][0] = x[inx];
        p[i][1] = y[inx];
        p[i][2] = z[inx];
        printf("%lf %lf %lf\n", x[inx], y[inx], z[inx]);
    }
}
