#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define pii pair<int,int>
#define mp make_pair
#define fs first
#define sc second
#define ll long long
using namespace std;
const int MAX = 600010;
const int mx=600010;
const int dx=9000000;

int tree[2][dx],lefto[2][dx],righto[2][dx],ps[2];
int root[2][mx],par[mx];
ll ans;

int txt[MAX]; //input
int iSA[MAX], SA[MAX]; //output
int cnt[MAX], nexto[MAX]; //internal
bool bh[MAX], b2h[MAX];
bool smaller_first_char(int a, int b){
  return txt[a] < txt[b];
}

void suffixSort(int n){
  for (int i=0; i<n; ++i){
    SA[i] = i;
  }
  sort(SA, SA + n, smaller_first_char);
  for (int i=0; i<n; ++i){
    bh[i] = i == 0 || txt[SA[i]] != txt[SA[i-1]];
    b2h[i] = false;
  }

  for (int h = 1; h < n; h <<= 1){
    int buckets = 0;
    for (int i=0, j; i < n; i = j){
      j = i + 1;
      while (j < n && !bh[j]) j++;
      nexto[i] = j;
      buckets++;
    }
    if (buckets == n) break;
    for (int i = 0; i < n; i = nexto[i]){
      cnt[i] = 0;
      for (int j = i; j < nexto[i]; ++j){
        iSA[SA[j]] = i;
      }
    }

    cnt[iSA[n - h]]++;
    b2h[iSA[n - h]] = true;
    for (int i = 0; i < n; i = nexto[i]){
      for (int j = i; j < nexto[i]; ++j){
        int s = SA[j] - h;
        if (s >= 0){
          int head = iSA[s];
          iSA[s] = head + cnt[head]++;
          b2h[iSA[s]] = true;
        }
      }
      for (int j = i; j < nexto[i]; ++j){
        int s = SA[j] - h;
        if (s >= 0 && b2h[iSA[s]]){
          for (int k = iSA[s]+1; !bh[k] && b2h[k]; k++) b2h[k] = false;
        }
      }
    }
    for (int i=0; i<n; ++i){
      SA[iSA[i]] = i;
      bh[i] |= b2h[i];
    }
  }
  for (int i=0; i<n; ++i){
    iSA[SA[i]] = i;
  }
}
int lcp[MAX];
void getlcp(int n)
{
  for (int i=0; i<n; ++i)
    iSA[SA[i]] = i;

  lcp[0] = 0;

  for (int i=0, h=0; i<n; ++i)
  {
    if (iSA[i] > 0)
    {
      int j = SA[iSA[i]-1];
      while (i + h < n && j + h < n && txt[i+h] == txt[j+h])
          h++;
      lcp[iSA[i]] = h;

      if (h > 0)
        h--;
    }
  }
}
vector<int>name[mx];
set<int>my[mx];
int n;
set<int>::iterator it;

int query(int node,int st,int en,int l,int r,int bol)
{
   if(st>r or en<l or l>r or node==0)return 0;
   if(st>=l and en<=r)return tree[bol][node];
   int mid=(st+en)>>1;
   int ret=0;
   if(l<=mid)ret+=query(lefto[bol][node],st,mid,l,r,bol);
   if(r>mid)ret+=query(righto[bol][node],mid+1,en,l,r,bol);
   return ret;
}
int update(int node,int st,int en,int l,int x,int bol)
{
    if(node==0)node=++ps[bol];
    if(st==en)
    {
       tree[bol][node]=x;
       return node;
    }
    int mid=(st+en)>>1;
    if(l<=mid)lefto[bol][node]=update(lefto[bol][node],st,mid,l,x,bol);
    else righto[bol][node]=update(righto[bol][node],mid+1,en,l,x,bol);
    tree[bol][node]=tree[bol][lefto[bol][node]]+tree[bol][righto[bol][node]];
    return node;
}
void clr()
{
   for(int j=0;j<2;j++)
   {
      for(int i=1;i<=ps[j];i++)
      {
         tree[j][i]=0;
         lefto[j][i]=0;
         righto[j][i]=0;
      }
      ps[j]=0;
   }
}
int findo(int x)
{
   if(x==par[x])return x;
   return par[x]=findo(par[x]);
}
int last[mx];
void cal(int x,int y,int r)
{
    int c=x-last[y];
    ans+=1LL*(n-y+1)*c*r;
}
void mergee(int x,int y,int c)
{
   if(my[x].size()>my[y].size())swap(x,y);
  // cout<<x<<" "<<y<<endl;
 int g=0;
 set<int>::iterator it,it2;
    for( it=my[x].begin();it!=my[x].end();it++)
   {
           int l=*it;
           it2=my[y].upper_bound(l);
           if(it2!=my[y].end())
           {
              cal(l,*it2,c);
              last[*it2]=l;
           }
           if(it2!=my[y].begin())
           {
              it2--;
              if(*it2>last[l])
              {
                 cal(*it2,l,c);
                 last[l]=*it2;
              }
           }
   }
    for( it=my[x].begin();it!=my[x].end();it++)
   {
           int l=*it;
        my[y].insert(l);
   }

   par[x]=y;
}
int much[mx][22];
int lcp_query(int x,int y)
{
   if(x>y)swap(x,y);
   x++;
   int k=log2(y-x+1);
   int c=much[x][k];
   int d=much[y-(1<<k)+1][k];
   return min(c,d);

}
vector<pii>ara[mx];
void process(vector<pii>&vc,int n,int r)
{
    clr();
    set<int>s;
    set<int>::iterator it;
    for(int i=1;i<vc.size();i++)
    {
       int c=lcp_query(vc[i-1].fs,vc[i].fs);
       s.insert(-c);
       ara[c].pb({vc[i-1].sc,vc[i].sc});
    }
    for(int i=1;i<=n;i++){
    par[i]=i;
    my[i].clear();
    my[i].insert(i);
     last[i]=0;
    }
 //   if(r==2)cout<<tree[0][root[1][0]]<<endl;
    for(it=s.begin();it!=s.end();it++)
    {
        int c=*it;
        c*=-1;
      //  if(c==0)break;

        for(int j=0;j<ara[c].size();j++)
        {
           int x=ara[c][j].fs;
           int y=ara[c][j].sc;
           int e=findo(x);
           int f=findo(y);
           assert(f!=e);
           //cout<<f<<" "<<e<<endl;
           mergee(f,e,min(c,r));
        }
        ara[c].clear();
    }
}
int main()
{
    int i,j,k,l,m,pos=0;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
       name[i].resize(m+1);
       for(int j=1;j<=m;j++){
       scanf("%d",&l);
       name[i][j]=pos++;
         txt[pos-1]=l;
       }
    }
    suffixSort(pos);
    getlcp(pos);
    for(int i=0;i<pos;i++)
    {
         much[i][0]=lcp[i];
    }
    for(int j=1;(1<<j)<pos;j++)
    {
       for(int i=0;i+(1<<(j-1))<pos;i++)
       {
          much[i][j]=min(much[i][j-1],much[i+(1<<(j-1))][j-1]);
       }
    }
    for(int j=1;j<=m;j++)
    {
       vector<pii>vc;
       for(int i=1;i<=n;i++)
       {
          int x=name[i][j];
          int p=iSA[x];
          vc.push_back(mp(p,i));
       }
       sort(vc.begin(),vc.end());
       process(vc,n,m-j+1);
    }
    ll tot=0;
    for(int j=1;j<=m;j++)
    {
       int sum=0;
       for(int i=1;i<=n;i++)
       {
          int c=n-i+1;
          sum+=i;
          tot+=1LL*(m-j+1)*i*c;
       }
    }
   // cout<<tot<<endl;
    tot-=ans;
    cout<<tot<<endl;
}
