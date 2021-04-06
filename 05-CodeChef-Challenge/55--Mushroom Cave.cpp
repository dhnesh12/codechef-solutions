#include <stdio.h>
#include <iostream>
 
using namespace std;
 
//#define DISK
 
int N, M, K, flag;
char q[102][102];
 
void visit(int u, int v, int steps, string s, string buch)
{
s=s+buch;
 
if(flag) return;
if(steps<K && u==M-1 && v==N-1)
	{
	cout<<s<<endl;
	flag=1;
	return;
	}
if(q[u][v]=='t')
	{
	q[u][v]='.';
	steps=0;
	}
steps++;
if(steps<=K)
	{
	if(v<N-1 && q[u][v+1]!='#') visit(u,v+1,steps,s,"E");
	if(u<M-1 && q[u+1][v]!='#') visit(u+1,v,steps,s,"S");
	if(v>0 && q[u][v-1]!='#') visit(u,v-1,steps,s,"W");
	if(u>0 && q[u-1][v]!='#') visit(u-1,v,steps,s,"N");
	}
}
 
main()
{
int t, i;
 
scanf("%d",&t);
while(t--)
	{
	flag=0;
	scanf("%d %d %d",&M,&N,&K);
	for(i=0; i<M; i++)
		scanf("%s",q[i]);
	visit(0,0,0,"","");
	}
} 