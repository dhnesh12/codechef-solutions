#include <stdio.h>
#include <stdlib.h>
#define siz 100000
#define S(a,b) if(a)return(b)
#define C(a) if(a)continue
 
typedef struct {
int x, n;
}st;
 
int o[siz];
st e[siz], *w[siz];
 
int A(const void *a, const void *b)
{
st *p=*(st**)a;
st *q=*(st**)b;
S(p->x<q->x,-1);
S(p->x>q->x,1);
S(p->n<q->n,-1);
S(p->n>q->n,1);
S(1,0);
}
 
main()
{
int fall, i, j, k, n, b, tmp;
for(scanf("%d",&fall); fall--; printf("%d\n",tmp))
	{
	for(i=!scanf("%d",&n); i<n; scanf("%d",&e[i].x),e[i].n=i,w[i]=e+i,o[i++]=0);
	qsort(w,n,sizeof(st*),A);
	for(i=!(b=1); i<n; i++)
		{
		C(o[i]);
		for(j=i+1; j<n&&o[j]; j++);
		C(j>=n);
		if(w[i]->n>w[j]->n)
			b++;
		else
			continue;
		for(k=j+1; k<n&&w[k]->x==w[j]->x&&w[k]->n<w[i]->n; k++);
		C(k>=n||w[k]->x!=w[j]->x);
		for(;k<n&&w[k]->x==w[j]->x; o[k++]=1);
		}
	for(tmp=0; b>1; b=(b+1)/2,tmp++);
	}
return 0;
}

