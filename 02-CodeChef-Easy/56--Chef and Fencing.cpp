#include<bits/stdc++.h>
using namespace std;
#define m1 -2147483648
#define m2 2147483647
int main(){ios_base::sync_with_stdio(false); cin.tie(NULL); int N, M; cin >> N >> M;
    long long int maxa = m1, maxb = m1, mina = m2, minb = m2;
    for (int i = 0; i < N; i++){int x, y; cin >> x >> y; int a = M*y+x, b = y-M*x; if (b > maxb){maxb = b;}
        if (b < minb){minb = b;} if (a < mina){mina = a;} if (a > maxa){maxa = a;}
	    }cout << fixed << setprecision(6); cout << 2*(maxa-mina+maxb-minb)/sqrt(1+M*M) << endl;}