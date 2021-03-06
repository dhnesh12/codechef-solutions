#include <bits/stdc++.h>
using namespace std;
#define f0(i, a, b) for (int i = a; i < b; i ++)
#define f1(i, a, b) for (int i = a; i <= b; i ++)
template <class T> void chkmax(T &a, T b) {if (a < b) a = b;}
template <class T> void chkmin(T &a, T b) {if (a > b) a = b;}

const int inf = 0x3f3f3f3f;

char nc() {
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
void read(int &x){
	char c=nc(),b=1;
	for (;!(c>='0'&&c<='9'||c==EOF);c=nc()) if (c=='-') b=-b;
	for (x=0;c>='0'&&c<='9';x=x*10+c-'0',c=nc()); x*=b;
}

#define N 1005

int n, m;
int d[N], mn[N], id[N], mx[N];
int a[N][N], b[N][N];
bool vis[N];

bool cmp(int x, int y) {
    return mn[x] < mn[y];
}

int main() {
    int T;
    for (read(T); T --; ) {
		read(n), read(m);
        f1(i, 1, n) read(d[i]);
        f1(i, 1, n) f1(j, 1, m) read(a[i][j]);
        f1(i, 1, n) f1(j, 1, m) {
			read(b[i][j]);
            if (!b[i][j]) a[i][j] = inf;
        }
        f1(j, 1, m) mn[j] = 1, id[j] = j;
        f1(i, 1, n) if (d[i]) {
            f1(j, 1, m) chkmax(mn[j], a[i][j]);
        }
        sort(id+1, id+m+1, cmp);
        bool flag = 0;
        int pos = 0;
        f1(j, 1, m) {
            int k = id[j];
            if (mn[k] == inf) break;
            bool res = 0;
            f1(i, 1, n) if (!d[i]) {
                chkmax(mx[i], a[i][k]);
                if (mx[i] <= mn[k]) res = 1;
            }
            if (!res) {
                pos = j; flag = 1;
                break;
            }
        }
        if (flag) {
            puts("YES");
            printf("%d %d\n", mn[id[pos]], pos);
            f1(i, 1, pos) printf("%d ", id[i]);
            puts("");
        }
        else puts("NO");
        f1(i, 1, n) mx[i] = 0;
    }
	return 0;
}
