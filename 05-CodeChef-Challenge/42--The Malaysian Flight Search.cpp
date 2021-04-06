/*
	"Why do we fall? So we can learn how to pick ourselves up."
	- Alfred, Batman Begins -
*/

# include <iostream>
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <set>
# include <cstring>
# include <string.h>
# include <sstream>
# include <map>
# include <queue>
# include <vector>

# define mp make_pair
# define LL long long
# define vi vector<int>
# define pqu priority_queue
# define iasc int,vector<int>,greater<int>
# define LLasc  LL,vector<LL>,greater<LL>
# define ins push_back
# define pii pair<int,int>
# define fi first
# define se second

inline void in(int &MAGNUS) {scanf("%d",&MAGNUS);}
inline void out(int MAGNUS) {printf("%d\n",MAGNUS);}
inline void in(int &MAGNUS,int &CLAR) {scanf("%d%d",&MAGNUS,&CLAR);}
inline void out(int MAGNUS,int CLAR) {printf("%d %d\n",MAGNUS,CLAR);}

inline void inl(LL &LIV) {scanf("%lld",&LIV);}
inline void inl(LL &LIV,LL &MART) {scanf("%lld%lld",&LIV,&MART);}
inline void outl(LL LIV) {printf("%lld\n",LIV);}
inline void outl(LL LIV, LL MART) {printf("%lld %lld\n",LIV,MART);}

# define FORU(a,b,c) for(int a=b; a<=c; a++)
# define FORD(a,b,c) for(int a=b; a>=c; a--)
# define FOR(a,b) for(int a=1; a<=b; a++)
# define FORA(a,b) for(auto (a) : (b))
# define REP(a,b) for(int a=0; a<b; a++)
# define RESET(a) memset(a,0,sizeof(a))
# define MEMO(a) memset(a,-1,sizeof(a))
# define ALL(a) (a).begin(),(a).end()
# define RNG(a,b) (a)+1,(a)+(b)+1
# define BSL(a,b) lower_bound(ALL(a),(b))-(a).begin()
# define BSLX(a,b,c) lower_bound((a)+1,(a)+(b)+1,(c))-a
# define BSU(a,b) upper_bound(ALL(a),(b))-(a).begin()
# define BSUX(a,b,c) upper_bound((a)+1,(a)+(b)+1,(c))-a
# define DEBUG puts("this-part-has-been-reach")

using namespace std;

int mxx=-(1<<30), mxy=-(1<<30), mnx=1<<30, mny=1<<30;
short area[1035][1035];
int x[200005], y[200005];
int qx[2000005], qy[2000005];
int N,M,radius,cost,id,qid;

const int dx[]={-1,0,1,0};
const int dy[]={0,-1,0,1};

bool inside(int r,int c){
	return (0<=r && r<=1025 && 0<=c && c<=1025);	
}

bool query(int id,int x,int y){
	cout << id << " " << x << " " << y << endl;
	fflush(stdout);
	string feedback;
	cin >> feedback;
	return (feedback=="yes");	
}

void bfs(int r,int c){
	//labelling all points outside search area
	int head=0, tail=0;
	qx[head]=r;
	qy[head]=c;
	tail++;
	area[r][c]=2;
	
	while(head!=tail){
		int rnow=qx[head];
		int cnow=qy[head];
		
		FORU(i,0,3){
			int nxr=rnow+dx[i], nxc=cnow+dy[i];
			if(!inside(nxr,nxc)) continue;
			if(area[nxr][nxc]!=0) continue;
			
			area[nxr][nxc]=2;
			qx[tail]=nxr;
			qy[tail]=nxc;
			tail++;
		}
		head++;
	}
}

int main(){
	
	in(N);
	FOR(i,N){
		in(x[i],y[i]);
		mxx=max(mxx,x[i]);
		mxy=max(mxy,y[i]);	
		mnx=min(mnx,x[i]);
		mny=min(mny,y[i]);
	}
	
	FOR(i,N) area[x[i]-mnx+1][y[i]-mny+1]=1;	//current area is a boundary of search area
	bfs(1025,1025);
	
	in(M);
	FOR(i,M){
		int radius,cost;
		in(radius,cost);
		if(radius==0){
			qid=i-1;
		}
	}
	
	FORU(i,0,1025){
		FORU(j,0,1025){
			if(area[i][j]<2){	//current point is inside search area
				int xask=i+mnx-1;
				int yask=j+mny-1;
				if(query(qid,xask,yask)){
					cout << "-1 " << xask << " " << yask << endl;
					fflush(stdout);
					return 0;
				}	
			}
		}
	}
	
	cout << "-1 -1 -1\n";
	fflush(stdout);

	return 0;
}




