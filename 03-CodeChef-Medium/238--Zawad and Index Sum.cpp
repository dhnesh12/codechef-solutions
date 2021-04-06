#include <bits/stdc++.h>
using namespace std;
const int mod=998244353;
const int mx=2000000;
#define ll long long


#define MAXN 1<<18
#define ll long long
ll ara[MAXN],ara2[MAXN],dp[MAXN];
namespace fft{
    int len, last = -1, step = 0, rev[MAXN];
    long long C[MAXN], D[MAXN], P[MAXN], Q[MAXN];

	struct complx{
        long double real, img;
        inline complx(){
            real = img = 0.0;
        }
        inline complx conjugate(){
            return complx(real, -img);
        }
        inline complx(long double x){
            real = x, img = 0.0;
        }
        inline complx(long double x, long double y){
            real = x, img = y;
        }
        inline complx operator + (complx other){
            return complx(real + other.real, img + other.img);
        }
        inline complx operator - (complx other){
            return complx(real - other.real, img - other.img);
        }
        inline complx operator * (complx other){
            return complx((real * other.real) - (img * other.img), (real * other.img) + (img * other.real));
        }
    } u[MAXN], v[MAXN], f[MAXN], g[MAXN], dp[MAXN], inv[MAXN];

    inline long long round_half_even(long double x){
        long long res = abs(x) + 0.5;
        if (x < 0) res = -res;
        return res;
    }
    void build(int& a, long long* A, int& b, long long* B){
        while (a > 1 && A[a - 1] == 0) a--;
        while (b > 1 && B[b - 1] == 0) b--;

	    len = 1 << (32 - __builtin_clz(a + b) - (__builtin_popcount(a + b) == 1));
        for (int i = a; i < len; i++) A[i] = 0;
        for (int i = b; i < len; i++) B[i] = 0;

		if (!step++){
            dp[1] = inv[1] = complx(1);
            for (int i = 1; (1 << i) < MAXN; i++){
                double theta = (2.0 * acos(0.0)) / (1 << i);
                complx mul = complx(cos(theta), sin(theta));
                complx inv_mul = complx(cos(-theta), sin(-theta));

                int lim = 1 << i;
                for (int j = lim >> 1; j < lim; j++){
                    dp[2 * j] = dp[j], inv[2 * j] = inv[j];
                    inv[2 * j + 1] = inv[j] * inv_mul;
                    dp[2 * j + 1] = dp[j] * mul;
                }
            }
        }

        if (last != len){
            last = len;
            int bit = (32 - __builtin_clz(len) - (__builtin_popcount(len) == 1));
            for (int i = 0; i < len; i++) rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (bit - 1));
        }
	}
	void transform(complx *in, complx *out, complx* ar){
	    for (int i = 0; i < len; i++) out[i] = in[rev[i]];
	    for (int k = 1; k < len; k <<= 1){
            for (int i = 0; i < len; i += (k << 1)){
                for (int j = 0; j < k; j++){
                    complx z = out[i + j + k] * ar[j + k];
                    out[i + j + k] = out[i + j] - z;
                    out[i + j] = out[i + j] + z;
                }
            }
	    }
	}
	void transform_unrolled(complx *in, complx *out, complx* ar){
	    for (int i = 0; i < len; i++) out[i] = in[rev[i]];
	    for (int k = 1; k < len; k <<= 1){
            for (int i = 0; i < len; i += (k << 1)){
                complx z, *a = out + i, *b = out + i + k, *c = ar + k;
                if (k == 1){
                    z = (*b) * (*c);
                    *b = *a - z, *a = *a + z;
                }

                for (int j = 0; j < k && k > 1; j += 2, a++, b++, c++){
                    z = (*b) * (*c);
                    *b = *a - z, *a = *a + z;
                    a++, b++, c++;
                    z = (*b) * (*c);
                    *b = *a - z, *a = *a + z;
                }
            }
	    }
	}
	bool equals(int a, long long* A, int b, long long* B){
        if (a != b) return false;
        for (a = 0; a < b && A[a] == B[a]; a++){}
        return (a == b);
	}
	int square(int a, long long* A){
        build(a, A, a, A);
        for (int i = 0; i < len; i++) u[i] = complx(A[i], 0);
        transform_unrolled(u, f, dp);
        for (int i = 0; i < len; i++) u[i] = f[i] * f[i];
        transform_unrolled(u, f, inv);
        for (int i = 0; i < len; i++) A[i] = round_half_even(f[i].real / (long double)len);
        return a + a - 1;
	}
	int multiply(int a, long long* A, int b, long long* B){
	    if (equals(a, A, b, B)) return square(a, A); /// Optimization

		build(a, A, b, B);
		for (int i = 0; i < len; i++) u[i] = complx(A[i], B[i]);
		transform_unrolled(u, f, dp);
		for (int i = 0; i < len; i++){
            int j = (len - 1) & (len - i);
            u[i] = (f[j] * f[j] - f[i].conjugate() * f[i].conjugate()) * complx(0, -0.25 / len);
		}
		transform_unrolled(u, f, dp);
		for (int i = 0; i < len; i++) A[i] = round_half_even(f[i].real);
		return a + b - 1;
	}

	int mod_multiply(int a, long long* A, int b, long long* B, int mod,long long *tp){
	    build(a, A, b, B);
	    int flag = equals(a, A, b, B);
	    for (int i = 0; i < len; i++) A[i] %= mod, B[i] %= mod;
	    for (int i = 0; i < len; i++) u[i] = complx(A[i] & 32767, A[i] >> 15);
	    for (int i = 0; i < len; i++) v[i] = complx(B[i] & 32767, B[i] >> 15);

		transform_unrolled(u, f, dp);
		for (int i = 0; i < len; i++) g[i] = f[i];
		if (!flag) transform_unrolled(v, g, dp);

		for (int i = 0; i < len; i++){
            int j = (len - 1) & (len - i);
            complx c1 = f[j].conjugate(), c2 = g[j].conjugate();

            complx a1 = (f[i] + c1) * complx(0.5, 0);
			complx a2 = (f[i] - c1) * complx(0, -0.5);
			complx b1 = (g[i] + c2) * complx(0.5 / len, 0);
			complx b2 = (g[i] - c2) * complx(0, -0.5 / len);
			v[j] = a1 * b2 + a2 * b1;
			u[j] = a1 * b1 + a2 * b2 * complx(0, 1);
		}
		transform_unrolled(u, f, dp);
		transform_unrolled(v, g, dp);

        long long x, y, z;
		for (int i = 0; i < len; i++){
            x = f[i].real + 0.5, y = g[i].real + 0.5, z = f[i].img + 0.5;
            tp[i] = (x + ((y % mod) << 15) + ((z % mod) << 30)) % mod;
		}
		return a + b - 1;
	}
}
int po[mx],m;
char str[mx],pat[mx];

int ans[mx],lps[mx];
int func(int x)
{
    if(x<0)x+=mod;
   ll c=1LL*x*(x+1);
   c%=mod;
   c=1LL*c*499122177;
   return c%=mod;
}
void runc(int m)
{
    // length of the previous longest prefix suffix
    int len = 0;
    int M=m;
    lps[0] = 0; // lps[0] is always 0

    // the loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else // (pat[i] != pat[len])
        {
            if (len != 0) {
                len = lps[len - 1];

            }
            else // if (len == 0)
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}
void take_func(int m)
{
  //  vector<int>vc,ac;
    memset(ara,0,sizeof ara);
    memset(ara2,0,sizeof ara2);
    memset(dp,0,sizeof dp);
   for(int i=0;i<m;i++)
   {
      ara[i]=str[i]-97;
     ara2[i]=po[i];
   }
   fft::mod_multiply(m,ara,m,ara2,mod,dp);
}
int ext[mx];
int main()
{
    po[0]=1;
    for(int i=1;i<=1000005;i++)
    {
       po[i]=1LL*po[i-1]*26%mod;
    }
    int ts;
    cin>>ts;
    while(ts--){
    //int m,n;
    memset(lps,0,sizeof lps);
    memset(ans,0,sizeof ans);
    memset(ext,0,sizeof ext);
    int n;
    int pv=0;
    scanf("%d%d",&m,&n);
    scanf("%s",str);
    for(int i=0;i<m;i++)pat[i]=str[i];

  //  for(int i=0;i<=m;i++)dp[i]=-1;

    take_func(m);
    ll sum=0;
    for(int i=0;i<=m;i++)
    {
        int x;
        if(i==0)x=0;
        else x=dp[i-1];

        int rem=n-i;
        int koyta=po[rem];
        int c=i;
        int a=po[c];
        ans[c]=(1LL*x*koyta)%mod;
        int xxx=func(koyta-1);
        ans[c]+=(1LL*a*xxx)%mod;
        ans[c]%=mod;
      //  cout<<ans[c]<<" "<<c<<endl;
    }
    runc(m);
    for(int i=m;i>0;i--)
    {
      int c=0;
      //if(i>1)
      {
        c=lps[i-1];
      }
  //     cout<<c<<" "<<i<<endl;
       ans[i]-=ext[i];
       if(ans[i]<0)ans[i]+=mod;
       ext[c]+=(ext[i]+ans[i])%mod;
       ext[c]%=mod;
    }
    ans[0]-=ext[0];
    if(ans[0]<0)ans[0]+=mod;
    for(int i=0;i<=m;i++)
    {
       if(i)printf(" ");
       printf("%d",ans[i]);
    }
    cout<<endl;
    }



}