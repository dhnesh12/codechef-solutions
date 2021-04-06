#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
typedef long long LL;
const int N = 100010,sqrtN = 320;
inline int getint()
{
	int r = 0,s = 0;char c = getchar();for(;!isdigit(c);c = getchar()) s |= c == '-';
	for(;isdigit(c);c = getchar()) r = (((r << 2) + r) << 1) + (c ^ '0');return s ? -r : r;
}
int T,q;
char buf[N];
int a[N],b[N],nc,n;
LL f[sqrtN][N][3],tmp[N][3];
int bc;
int lb[sqrtN],rb[sqrtN],bel[N];
inline LL calc(int l,int r,int t)
{
	LL ans[3] = {0,0,0};
	memset(tmp,0,sizeof(tmp));
	tmp[a[l]][0] = 1;
	tmp[a[l]][1] = l;
	tmp[a[l]][2] = 1LL * l * l;
	for(int i = l + 1;i <= r;i++)
	{
		ans[0] += tmp[a[i]][0];
		ans[1] += 1LL * tmp[a[i]][0] * i - tmp[a[i]][1];
		ans[2] += tmp[a[i]][2] + 1LL * i * i * tmp[a[i]][0] - 2LL * tmp[a[i]][1] * i;
		tmp[a[i]][0] += 1;
		tmp[a[i]][1] += i;
		tmp[a[i]][2] += 1LL * i * i;
	}
	return ans[t];
}
inline LL CALC(int l,int L,int R,int r,int t)
{
	LL ans[3] = {0,0,0};
	memset(tmp,0,sizeof(tmp));
	for(int i = l;i <= L;i++)
	{
		tmp[a[i]][0] += 1;
		tmp[a[i]][1] += i;
		tmp[a[i]][2] += 1LL * i * i;
	}
	for(int i = R;i <= r;i++)
	{
		ans[0] += tmp[a[i]][0];
		ans[1] += 1LL * tmp[a[i]][0] * i - tmp[a[i]][1];
		ans[2] += tmp[a[i]][2] + 1LL * i * i * tmp[a[i]][0] - 2LL * tmp[a[i]][1] * i;
	}
	return ans[t];
}
int main()
{
	T = getint();while(T--)
	{
		scanf("%s",buf + 1);n = strlen(buf + 1) + 1;
		a[0] = 0;for(int i = 1;i < n;i++) b[i] = a[i] = a[i - 1] ^ (1 << (buf[i] - 'a'));
		std::sort(b,b + n);
		nc = std::unique(b,b + n) - b;
		for(int i = 0;i < n;i++) a[i] = std::lower_bound(b,b + nc,a[i]) - b;
		// memset(lb,0,sizeof(lb));memset(rb,0,sizeof(rb));memset(bel,0,sizeof(bel));
		bc = 0;
		while(rb[bc] != n - 1)
		{
			bc++;
			lb[bc] = (bc - 1) * sqrtN;
			rb[bc] = std::min(n - 1,bc * sqrtN - 1);
			for(int i = lb[bc];i <= rb[bc];i++) bel[i] = bc;
		}
		for(int u = 1;u <= bc;u++)
		{
			int p = lb[u];
			f[u][p][0] = f[u][p][1] = f[u][p][2] = 0;
			memset(tmp,0,sizeof(tmp));
			tmp[a[p]][0] = 1;
			tmp[a[p]][1] = p;
			tmp[a[p]][2] = 1LL * p * p;
			for(int j = p - 1;~j;j--)
			{
				f[u][j][0] = f[u][j + 1][0] + tmp[a[j]][0];
				f[u][j][1] = f[u][j + 1][1] + tmp[a[j]][1] - 1LL * tmp[a[j]][0] * j;
				f[u][j][2] = f[u][j + 1][2] + tmp[a[j]][2] + 1LL * tmp[a[j]][0] * j * j - 2LL * j * tmp[a[j]][1];
				tmp[a[j]][0] += 1;
				tmp[a[j]][1] += j;
				tmp[a[j]][2] += 1LL * j * j;
			}
			memset(tmp,0,sizeof(tmp));
			tmp[a[p]][0] = 1;
			tmp[a[p]][1] = p;
			tmp[a[p]][2] = 1LL * p * p;
			for(int j = p + 1;j < n;j++)
			{
				f[u][j][0] = f[u][j - 1][0] + tmp[a[j]][0];
				f[u][j][1] = f[u][j - 1][1] + 1LL * tmp[a[j]][0] * j - tmp[a[j]][1];
				f[u][j][2] = f[u][j - 1][2] + tmp[a[j]][2] + 1LL * tmp[a[j]][0] * j * j - 2LL * j * tmp[a[j]][1];
				tmp[a[j]][0] += 1;
				tmp[a[j]][1] += j;
				tmp[a[j]][2] += 1LL * j * j;
			}
		}
		LL va = 0,vb = 0;
		q = getint();while(q--)
		{
			int x = (getint() + va) % (n - 1) + 1,y = (getint() + vb) % (n - 1) + 1;
			//int x = getint(),y = getint();
			int t = getint();
			if(x > y) std::swap(x,y);x--;
			LL ans = 0;
			LL ta = 0;
			int L = bel[x],R = bel[y];
			//printf("# %d %d %d %d\n",x,y,L,R);
			if(L == R) ans = calc(x,y,t);
			else
			{
				ans = f[L + 1][y][t] + f[R][x][t] - f[L + 1][lb[R]][t];
				ta = ans;
				// printf("C %d %d %d %d %d\n",x,rb[L],lb[R] + 1,y,t);
				ans += CALC(x,rb[L],lb[R] + 1,y,t);
			}
			// printf("%lld %lld\n",ans - ta,ta);
			printf("%lld\n",ans);
			va = vb;vb = ans;
		}
	}
	return 0;
}
