#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
int t,n,b,i,j,m,a[77],c[77],en;
long long e[100100],x,r;
char s[7];
vector <int> f[100100],d;
void rec(int i, long long x) {
  if (i>m) { e[en++]=x; return; }
  long long z=x;
  for (int j=0; j<=c[i]; j++) { rec(i+1,z); z*=a[i]; }
}
int main() {
  scanf("%d",&t);
  while (t--) {
    scanf("%s",&s);
    n=strlen(s); r=-1;
    for (b=j=0; j<n; j++) if (s[j]<='9') b=max(b,s[j]-'0'+1); else b=max(b,s[j]-'A'+11);
    if (n==1) { printf("%d\n",b-1); continue; } else if (b<2) b=2;
    for (; ; b++) {
      for (x=j=0; j<n; j++) if (s[j]<='9') x=x*b+s[j]-'0'; else x=x*b+s[j]-'A'+10;
      if (r>0 && x>=r) break;
      en=m=0;
      for (j=2; j<b && j*j<=x; j++) if (x%j==0) {
        a[++m]=j; c[m]=1; x/=j;
        while (x%j==0) { c[m]++; x/=j; }
      }
      if (x>1) {
        if (x>=b) continue;
        a[++m]=x; c[m]=1;
      }
      rec(1,1); sort(e,e+en);
      for (i=1; i<en; i++) {
        f[i].clear();
        for (j=i-1; j>=0 && e[i]/e[j]<b; j--) if (e[i]%e[j]==0) {
          d=f[j];
          if (j>0 && d.size()==0) continue;
          d.push_back(int(e[i]/e[j]));
          if (f[i].size()>0 && d.size()>f[i].size()) continue;
          sort(d.begin(),d.end());
          if (f[i].size()==0 || d.size()<f[i].size() || (d.size()==f[i].size() && d<f[i])) f[i]=d;
        }
      }
      d=f[en-1];
      if (d[0]!='-') {
        for (x=j=0; j<d.size(); j++) x=x*b+d[j];
        if (r==-1 || x<r) r=x;
      }
    }
    printf("%lld\n",r);
  }
  return 0;
}
