#include <cstdio>
#include <cmath>

int main()
{
    double S, V;
    int T;
    scanf("%d", &T);

    for (int i = 0; i < T; i++)
    {

        scanf("%lf %lf", &S, &V);

        double cnst = 3.0 / 2;
        double invS = 1.0 / V;
        double lst = S;

        double res = (2.0 * S) / (3.0 * V);

        printf("%.8lf\n", res);
    }
}