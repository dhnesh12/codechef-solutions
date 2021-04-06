#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#include<set>
using namespace std;
#define MV_R 0
#define MV_L 1
#define MV_U 2
#define MV_D 3
#define MAXN 23
#define MAXQ 10100
#define INF 0x3f3f3f3f
const double alpha=5;
const double beta=0.0;
int n,m;
inline bool isball(char ch)
{
		return ch=='+' || ch=='-' || ch=='=' || ch=='%';
}
int hcnt,hx[10],hy[10];
struct map_t
{
		char mp[MAXN][MAXN];
		int tp,te,tn,tr;
		int scr;
		bool rev;
		map_t()
		{
				memset(mp,0,sizeof(mp));
				tp=te=tn=tr=scr=rev=0;
		}
		void Init()
		{
				hcnt=0;
				tp=te=tn=tr=0;
				for (int i=1;i<=n;i++)
						for (int j=1;j<=m;j++)
								switch (mp[i][j])
								{
										case '+':tp++;break;
										case '-':tn++;break;
										case '=':te++;break;
										case '%':tr++;break;
										case '*':hx[hcnt]=i,hy[hcnt]=j,hcnt++;break;
								}
		}
		void worst()
		{
				for (int i=0;i<=n+1;i++)
						for (int j=0;j<=m+1;j++)
								mp[i][j]='.';
				for (int i=1;i<=n;i++)
						for (int j=1;j<=m;j++)
								mp[i][j]='-';
				mp[1][1]='*';
				scr=-10000;
		}
		int move(int p)
		{
				scr--;
				if (p==MV_R)
				{
						for (register int i=1;i<=n;i++)
								for (register int j=m;j>0;j--)
										if (mp[i][j]=='.' || mp[i][j]=='*')
												if (isball(mp[i][j-1]))
												{
														mp[i][j]=mp[i][j-1];
														mp[i][j-1]='.';
												}
				}else if (p==MV_L)
				{
						for (register int i=1;i<=n;i++)
								for (register int j=1;j<=m;j++)
										if (mp[i][j]=='.' || mp[i][j]=='*')
										{
												if (isball(mp[i][j+1]))
												{
														mp[i][j]=mp[i][j+1];
														mp[i][j+1]='.';
												}
										}
				}else if (p==MV_U)
				{
						for (register int i=1;i<=n;i++)
								for (register int j=1;j<=m;j++)
										if (mp[i][j]=='.' || mp[i][j]=='*')
										{
												if (isball(mp[i+1][j]))
												{
														mp[i][j]=mp[i+1][j];
														mp[i+1][j]='.';
												}
										}
				}else if (p==MV_D)
				{
						for (register int i=n;i>=1;i--)
								for (register int j=1;j<=m;j++)
										if (mp[i][j]=='.' || mp[i][j]=='*')
										{
												if (isball(mp[i-1][j]))
												{
														mp[i][j]=mp[i-1][j];
														mp[i-1][j]='.';
												}
										}
				}
				for (register int i=0;i<hcnt;i++)
				{
						if (mp[hx[i]][hy[i]]=='+')
								scr+=rev?-5:5,tp--;
						if (mp[hx[i]][hy[i]]=='-')
								scr+=rev?5:-5,tn--;
						if (mp[hx[i]][hy[i]]=='=')
								te--;
				}
				for (register int i=0;i<hcnt;i++)
				{
						if (mp[hx[i]][hy[i]]=='%')
								rev^=1,tr--;
						mp[hx[i]][hy[i]]='*';
				}
				return scr;
		}
		inline bool finish()
		{
				return !tp && !tn && !te && !tr;
		}
		inline int totball()
		{
				return tp+tn+te+tr;
		}
		void print()
		{
				for (int i=0;i<=n+1;i++)
				{
						for (int j=0;j<=m+1;j++)
						{
								if (mp[i][j]=='+')
										printf("%c",rev?'-':'+');
								else if (mp[i][j]=='-')
										printf("%c",rev?'+':'-');
								else
										printf("%c",mp[i][j]);
						}
						printf("\n");
				}
		}
		inline int GetValue(int alpha=5)const
		{
				return scr+(tr?alpha*(tp+tn):alpha*(rev?tn-tp:tp-tn))-(tr+tp+tn+te)/hcnt;
		}
}sss;

int main()
{
		int nn;
		srand(123);
		scanf("%d",&nn);
		while (nn--)
		{
				scanf("%d %d",&n,&m);
				sss=map_t();
				for (int i=0;i<=n+1;i++)
						for (int j=0;j<=m+1;j++)
								sss.mp[i][j]='.';
				string rres="";
				for (int i=1;i<=n;i++)
				{
						for (int j=1;j<=m;j++)
								do
										scanf("%c",&sss.mp[i][j]);
								while (sss.mp[i][j]==' ' || sss.mp[i][j]=='\r' || sss.mp[i][j]=='\n');
				}
				sss.Init();
				map_t tmp;
				int tries=0;
				pair<int,string> haha=make_pair(0,string(""));
				int cnt=0;
				while (true)
				{
						cnt++;
						rres="";
						map_t cur=sss;
						int alpha=rand()%3+1;
						while (!cur.finish())
						{
								map_t bstans;
								int t=rand()%2+1;
								int bst[4],ways[4];
								bst[0]=bst[1]=bst[2]=bst[3]=-INF;
								memset(ways,0,sizeof(ways));
								for (int s=0;s<(1<<t<<t);s++)
								{
										tmp=cur;
										int res=0;
										for (int j=0;j<t;j++)
										{
												tmp.move((s>>j>>j)&3);
												if (j==0 && tmp.totball()==cur.totball())
														res-=40;
										}
										if (tmp.tr==cur.tr)res-=40;
										res+=tmp.GetValue(alpha);
										if (tmp.totball()==cur.totball())
												res-=200;
										if (bst[s&3]<res)
												bst[s&3]=res,ways[s&3]=0;
										if (bst[s&3]==res)
												ways[s&3]++;

								}
								int choice=0;
								for (int i=1;i<4;i++)
										if (bst[i]>bst[choice] || (bst[i]==bst[choice] && rand()%(ways[i]+ways[choice])>ways[choice]))
												choice=i;
								cur.move(choice);
								switch(choice)
								{
										case MV_L:rres+='L';break;
										case MV_R:rres+='R';break;
										case MV_U:rres+='U';break;
										case MV_D:rres+='D';break;
								}
								//cur.print();printf("%d\n",cur.scr);
								if (cur.GetValue()<=haha.first)
										break;
						}
						if (cur.finish())
						{
								if (cur.scr>0)
								{
										tries++;
										haha=max(haha,make_pair(cur.scr,rres));
								}else
								{
										continue;
								}
						}
						if (haha.first && cnt>180)break;
				}
						printf("%s\n",haha.second.c_str());
		}
}