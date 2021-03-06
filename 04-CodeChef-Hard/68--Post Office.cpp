#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long int64;
const int oo=1000000000,mod=1000000037;
const int dx[]={1,0,-1,0};
const int dy[]={0,1,0,-1};
/*
	Number Theory
*/
const int pMod[]={421,563,4219};
int fact[3][5000],rev[3][5000];
void init() {
	for(int pi=0;pi<3;pi++) {
		for(int i=1;i<pMod[pi];i++) {
			int ret=1;
			while(ret%i)
			    ret+=pMod[pi];
			rev[pi][i]=ret/i;
		}
		
		fact[pi][0]=1;
		for(int i=1;i<pMod[pi];i++)
		    fact[pi][i]=fact[pi][i-1]*i%pMod[pi];
	}
}
void calcFactorial(int n,int pi,int &val,int &pow) {
	int p=pMod[pi];
	while(n>=p) {
		val=val*fact[pi][n%p]%p;
		if(((n/p)&1)&&val)
		    val=p-val;
		pow+=n/=p;
	}
	val=val*fact[pi][n]%p;
}
int comb(int x,int y) {
	if(x<0||y<0)
	    return 0;
	if(x==0||y==0)
	    return 1;
	
	int64 ans=0;
	const int coef[3]={933491721,257548855,808959499};
	for(int pi=0;pi<3;pi++) {
		int val1=1,pow1=0;
		int val2=1,pow2=0;
		calcFactorial(x+y,pi,val1,pow1);
		calcFactorial(x,pi,val2,pow2);
		calcFactorial(y,pi,val2,pow2);
		
		int val=0;
	    if(pow1==pow2)
			val=val1*rev[pi][val2]%pMod[pi];
 
//printf("%d\n",valFact[pi][x+y]);
 
		ans+=(int64)coef[pi]*val%mod;
		
		//printf("comb(%d,%d)=%d (mod %d)\n",x,y,val,pMod[pi]);
		
	}
	return ans%mod;
}
/*
	Main
*/
struct Point {
	int x,y,cnt;
};
bool operator<(const Point &p1,const Point &p2) {
	if(p1.x!=p2.x)
	    return p1.x<p2.x;
	else
	    return p1.y<p2.y;
}
 
const int maxN=1010;
int n,W,H;
Point p[maxN];
/*
	Method 1
	condition: n<=W,H
*/
int getPlug(int &bx,int &by,Point pl[]) {
	//Calc bx,by
    static bool v[maxN];
    memset(v,0,sizeof(v));
    for(int i=1;i<=n;i++)
        if(p[i].x<=n)
            v[p[i].x]=true;
	for(bx=0;v[bx];bx++);
	
	memset(v,0,sizeof(v));
    for(int i=1;i<=n;i++)
        if(p[i].y<=n)
            v[p[i].y]=true;
	for(by=0;v[by];by++);
	
	//printf("bx=%d by=%d\n",bx,by);
 
	//Init d[]
	static int d[maxN][maxN],cnt[maxN][maxN];
	for(int i=0;i<=bx;i++)
	for(int j=0;j<=by;j++)
	    d[i][j]=oo;
    for(int i=1;i<=n;i++)
	    if(p[i].x<bx&&p[i].y<by)
			d[p[i].x][p[i].y]=-1;
	d[0][0]=0,cnt[0][0]=1;
 
	//Init queue
	static int l[maxN*maxN][2];
	int lh=1,lt=0;
	#define ADD(x,y) ++lt,l[lt][0]=(x),l[lt][1]=(y)
	ADD(0,0);
 
	//BFS
	for(;lh<=lt;lh++) {
		int x=l[lh][0],y=l[lh][1];
		//printf("%d %d d=%d cnt=%d\n",x,y,d[x][y],cnt[x][y]);
		if(x<bx&&y<by)
			for(int dir=0;dir<4;dir++) {
				int x2=x+dx[dir],y2=y+dy[dir];
				if(0<=x2&&x2<=bx&&0<=y2&&y2<=by)
					if(d[x][y]+1<d[x2][y2]) {
	                	d[x2][y2]=d[x][y]+1;
	                	cnt[x2][y2]=cnt[x][y];
						ADD(x2,y2);
					} else if(d[x2][y2]==d[x][y]+1)
					    if((cnt[x2][y2]+=cnt[x][y])>=mod)
					        cnt[x2][y2]-=mod;
			}
	}
	
	//Find min dist
	int mind=oo;
	for(int i=1;i<=lt;i++) {
        int x=l[i][0],y=l[i][1],ret=d[x][y]+(bx-x)+(by-y);
        if(x==bx||y==by)
        	mind=min(mind,ret);
	}
	//Find bound vertex of min dist
	int nPl=0;
	for(int i=1;i<=lt;i++) {
        int x=l[i][0],y=l[i][1],ret=d[x][y]+(bx-x)+(by-y);
        if((x==bx||y==by)&&mind==ret)
			nPl++,pl[nPl].x=x,pl[nPl].y=y,pl[nPl].cnt=cnt[x][y];
			//printf("%d %d d=%d cnt=%d ret=%d\n",x,y,d[x][y],cnt[x][y],ret);
	}
	return nPl;
}
int solve2D() {
	//Calc lower-left plugs
	static Point l1[maxN*2],l2[maxN*2];
	int bx1,by1,n1=getPlug(bx1,by1,l1);
	
	//Calc upper-right plugs
	for(int i=1;i<=n;i++) {
	    p[i].x=W-p[i].x;
	    p[i].y=H-p[i].y;
	}
	int bx2,by2,n2=getPlug(bx2,by2,l2);
	
	//Fix
	for(int i=1;i<=n;i++) {
	    p[i].x=W-p[i].x;
	    p[i].y=H-p[i].y;
	}
	bx2=W-bx2,by2=H-by2;
	for(int i=1;i<=n2;i++) {
	    l2[i].x=W-l2[i].x;
	    l2[i].y=H-l2[i].y;
	}
	
	
 
    int64 ans=0;
    for(int i=1;i<=n1;i++)
    for(int j=1;j<=n2;j++)
        ans+=(int64)comb(l2[j].x-l1[i].x,l2[j].y-l1[i].y)*l1[i].cnt%mod*l2[j].cnt%mod;
//printf("ans=%d\n",int(ans%mod));
 
    sort(p+1,p+n+1);
	static int dp[maxN];
	for(int i=1;i<=n;i++) {
		int64 ret=0;
	    for(int j=1;j<=n1;j++)
	        ret+=(int64)comb(p[i].x-l1[j].x,p[i].y-l1[j].y)*l1[j].cnt%mod;
        //printf("tot[%d]=%d\n",i,int(ret%mod));
		for(int j=1;j<i;j++)
		    ret-=(int64)dp[j]*comb(p[i].x-p[j].x,p[i].y-p[j].y)%mod;
 
		
		if((ret%=mod)<0)
		    ret+=mod;
		dp[i]=ret;
		//printf("dp[%d]=%d\n",i,dp[i]);
		
		ret=0;
		for(int j=1;j<=n2;j++)
	        ret+=(int64)comb(l2[j].x-p[i].x,l2[j].y-p[i].y)*l2[j].cnt%mod;
        //printf("tot2[%d]=%d\n",i,int(ret%mod));
		ans-=ret%mod*dp[i]%mod;
	}
	
	if((ans%=mod)<0)
		ans+=mod;
	return ans;
}
/*
	Method 2
	condition: H<=100 (n<=100)
*/
const int maxSize=109;
int solve1D() {
	//Compute segments
	static int seg[maxSize][2];
	int nSeg=0;
	nSeg++,seg[nSeg][0]=seg[nSeg][1]=0;
 
	sort(p+1,p+n+1);
	for(int i=1;i<=n;i++)
	    if(p[i].x==seg[nSeg][1]+1)
	        seg[nSeg][1]++;
		else if(p[i].x>seg[nSeg][1]+1)
		    nSeg++,seg[nSeg][0]=seg[nSeg][1]=p[i].x;
 
	if(W==seg[nSeg][1]+1)
	    seg[nSeg][1]++;
	else if(W>seg[nSeg][1]+1)
		nSeg++,seg[nSeg][0]=seg[nSeg][1]=W;
 
	//Init dist
	static int dCur[maxSize],cntCur[maxSize];
	memset(dCur,194,sizeof(dCur));
	dCur[0]=-1,cntCur[0]=1;
 
	//Advance in each segments
	static int d[maxSize][maxSize],cnt[maxSize][maxSize];
    for(int si=1;si<=nSeg;si++) {
		int L=seg[si][0]-1,R=min(seg[si][1]+1,W);
		//printf("process %d~%d\n",L,R);
 
		//Init d[]
		for(int i=0;i<=R-L;i++)
		for(int j=0;j<=H;j++)
		    d[i][j]=oo,cnt[i][j]=0;
        memcpy(d[0],dCur,sizeof(dCur));
        memcpy(cnt[0],cntCur,sizeof(cntCur));
		for(int i=1;i<=n;i++)
		    if(L<=p[i].x&&p[i].x<=R)
		        d[p[i].x-L][p[i].y]=-1;
 
		//Init queue jumper!
		static pair<int,int> la[maxSize];
		int nla=0;
		for(int i=0;i<=H;i++)
		    if(dCur[i]>-oo)
		        la[++nla]=make_pair(dCur[i],i);
		sort(la+1,la+nla+1);
 
		//Init queue
		static int l[maxSize*maxSize][2];
		int lh=1,lt=0,pos=1;
 
		//BFS
		while(lh<=lt||pos<=nla) {
			int x,y;
			if(lh<=lt) {
				x=l[lh][0],y=l[lh][1];
				if(pos>nla||(d[x][y]<d[0][la[pos].second])) {
					lh++;
				    goto skip;
				}
			}
			x=0,y=la[pos++].second;
			//puts("jumper!");
			skip:;
 
			//printf("%d %d d=%d cnt=%d\n",x,y,d[x][y],cnt[x][y]);
			for(int dir=0;dir<4;dir++) {
				if(x==0&&dir)
				    continue;
 
				int x2=x+dx[dir],y2=y+dy[dir];
				if(0<=x2&&x2<=R-L&&0<=y2&&y2<=H)
					if(d[x][y]+1<d[x2][y2]) {
	                	d[x2][y2]=d[x][y]+1;
	                	cnt[x2][y2]=cnt[x][y];
						ADD(x2,y2);
					} else if(d[x2][y2]==d[x][y]+1)
					    if((cnt[x2][y2]+=cnt[x][y])>=mod)
					        cnt[x2][y2]-=mod;
			}
		}
		//Arrive another side
		memcpy(dCur,d[R-L],sizeof(dCur));
        memcpy(cntCur,cnt[R-L],sizeof(cntCur));
 
		//Run
		if(R<W) {
            //Disconnected
        	if(dCur[0]>=oo)
            	return 0;
 
			//Update
			int len=seg[si+1][0]-1-R;
			if(len) {
				for(int i=0;i<=H;i++) {
					int ret=0;
					for(int j=0;j<=H;j++)
					    if(dCur[j]+abs(i-j)==dCur[i])
							ret=(ret+(int64)cntCur[j]*comb(len-1,abs(i-j)))%mod;
					cnt[0][i]=ret;
				}
 
				for(int i=0;i<=H;i++)
					dCur[i]+=len;
				memcpy(cntCur,cnt[0],sizeof(cntCur));
			}
		}
	}
	return cntCur[H];
}
int main() {
	init();
	/*int kk=10000000;
	printf("%d\n",(int64)kk*(kk-1)/2%mod);
	//printf("%d %d %d\n",kk%pMod[0],kk%pMod[1],kk%pMod[2]);
	printf("comb=%d\n",comb(kk-2,2));
	//printf("%d *^%d\n",valFact[0][1000],powFact[0][1000]);*/
 
	int T;
	for(scanf("%d",&T);T;T--){
 
	scanf("%d%d%d",&W,&H,&n);
	for(int i=1;i<=n;i++)
	    scanf("%d%d",&p[i].x,&p[i].y);
	    
	for(int i=1;i<=n;i++)
	    if(!(0<=p[i].x&&p[i].x<=W&&0<=p[i].y&&p[i].y<=H))
	        p[i]=p[n],n--,i--;
 
	int ans;
	if(n<=W&&n<=H)
    	ans=solve2D();
	else {
		if(W<H) {
		    swap(W,H);
		    for(int i=1;i<=n;i++)
		    	swap(p[i].x,p[i].y);
		}
		if(H>100)
		    abort();
		    
		ans=solve1D();
	}
	printf("%d\n",ans);}
	scanf("%*s");
}   