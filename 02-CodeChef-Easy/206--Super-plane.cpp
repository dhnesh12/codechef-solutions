#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define REP(i,a,b) for(i=a;i<b;i++)
#define rep(i,n) REP(i,0,n)
typedef struct struct_vector_int{ int size,mem; int *d; }intVector;
intVector intVectorNull()
{
    intVector v;
    v.size=v.mem=0;
    return v;
}
void intVectorMemoryExpand(intVector *v)
{
  int i, *t, m;
  m=v->mem*2;
  if(m<5)
  m=5;
  t=(int*)malloc(m*sizeof(int));
  rep(i,v->size)
  t[i]=v->d[i];
  if(v->mem)
  free(v->d);
  v->d=t;
  v->mem=m;
}
void intVectorPushBack(intVector *v,int add)
{
  if(v->mem==v->size)
  intVectorMemoryExpand(v);
  v->d[(v->size)++] = add;
}
int intArrayBinarySearchSmallElement(int d[],int size,int n)
{
  int c = size/2; int i;
  if(size==1)
  {
      if(d[0]<n)
      return 0;
      return -1;
  }
  if(size<=0)
  return -1;
  if(d[c] < n)
  return intArrayBinarySearchSmallElement(d+c,size-c,n) + c;
  return intArrayBinarySearchSmallElement(d,c,n);
}
intVector edge[10010], st[10010], ed[10010], used[10010];
void intIntIntIntSort(int d[],int m1[],int m2[],int m3[],int s)
{
    int i=-1,j=s,k,t;
    if(s<=1)
    return;
    k=(d[0]+d[s-1])/2;
    for(;;)
    {
        while(d[++i]<k);
        while(d[--j]>k);
        if(i>=j)
        break;
        t=d[i];
        d[i]=d[j];
        d[j]=t;
        t=m1[i];
        m1[i]=m1[j];
        m1[j]=t;
        t=m2[i];
        m2[i]=m2[j];
        m2[j]=t;
        t=m3[i];
        m3[i]=m3[j];
        m3[j]=t;
    }
    intIntIntIntSort(d,m1,m2,m3,i);
    intIntIntIntSort(d+j+1,m1+j+1,m2+j+1,m3+j+1,s-j-1);
}
int main()
{
  int i,j,k,l,m,n;
  int next_node, next_time;
  int st_node, st_time, ed_node, ed_time;
  int size;
  int res;
  rep(i,10010)
  edge[i] = st[i] = ed[i] = used[i] = intVectorNull();
  scanf("%d",&size);
  while(size--)
  {
    scanf("%d",&m);
    n = 0;
    rep(i,10010)
    edge[i].size = st[i].size = ed[i].size = used[i].size = 0;
    while(m--)
    {
      scanf("%d%d%d%d",&i,&j,&k,&l);
      i--;
      k--;
      if(i >= n)
      n = i+1;
      if(k >= n)
      n = k+1;
      intVectorPushBack(edge+i, k);
      intVectorPushBack(st  +i, j);
      intVectorPushBack(ed  +i, l);
      intVectorPushBack(used+i, 0);
    }
    rep(i,n) intIntIntIntSort(st[i].d, edge[i].d, ed[i].d, used[i].d, st[i].size);
    scanf("%d%d%d%d",&st_node, &st_time, &ed_node, &ed_time);
    st_node--;
    ed_node--;
    res = 0;
    for(;;)
    {
      if(st_node == ed_node && st_time <= ed_time)
      break;
      k = intArrayBinarySearchSmallElement( st[st_node].d, st[st_node].size, st_time );
      k++;
      if(k==st[st_node].size)
      {
          res=-1;
          break;
      }
      if(used[st_node].d[k])
      {
          res=-1;
          break;
      }
      next_node = edge[st_node].d[k];
      next_time = ed[st_node].d[k];
      used[st_node].d[k] = 1;
      st_node = next_node;
      st_time = next_time;
      res++;
    }
    if(res<0)
    puts("No");
    else
    printf("Yes %d\n",res);
  }
  return 0;
}