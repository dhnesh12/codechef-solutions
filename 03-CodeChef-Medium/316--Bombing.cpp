#include <cstdio>
#include <algorithm>
using namespace std;
const int z=(1<<30);
struct node {
  int l,r,key;
} a[10000000];
int N,m,i,n,k,x,y,X[255555],Y[255555];
char s[7];
void add(int i, int L, int R, int x, int y, int z) {
  if (L==x && R==y) { a[i].key+=z; return; }
  int h=(L+R)/2;
  if (x<=h) {
    if (a[i].l==0) a[i].l=++n;
    add(a[i].l,L,h,x,min(y,h),z);
  }
  if (y>h) {
    if (a[i].r==0) a[i].r=++n;
    add(a[i].r,h+1,R,max(x,h+1),y,z);
  }
}
int get(int i, int L, int R, int x) {
  if (L==R) return a[i].key;
  int h=(L+R)/2;
  if (x<=h) return a[i].key+((a[i].l==0)?0:get(a[i].l,L,h,x));
       else return a[i].key+((a[i].r==0)?0:get(a[i].r,h+1,R,x));
}
int main() {
  scanf("%d%d",&N,&m); n=0;
  for (i=0; i<m; i++) {
    scanf("%s",s);
    if (s[0]=='B') {
      scanf("%d",&x);
      if (x<0 || x>N) x/=0;
      printf("%d\n",get(0,0,z-1,x));
    } else {
      scanf("%d%d",&x,&y);
      if (s[0]=='P') {
        X[++k]=x; Y[k]=y;
        add(0,0,z-1,x,y,1);
      } else {
        add(0,0,z-1,X[x],Y[x],-1);
        X[x]+=y; Y[x]+=y;
        if (X[x]<0 || Y[x]>=z) for (;;);
        add(0,0,z-1,X[x],Y[x],1);
      }
    }
  }
  return 0;
}
