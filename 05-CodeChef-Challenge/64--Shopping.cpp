

#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <climits>
#include <map>
#include <ctime>
typedef long long LL;
using namespace std;
 
#ifndef INTERACTIVE_ENABLED
namespace interactivity{
    void init(int &n,int &m,int v[],int a[]){
        scanf("%d%d",&n,&m);
        for(int i=0;i<n;++i)scanf("%d",v+i);
        for(int i=0;i<n;++i)scanf("%d",a+i);
    }
    void iatm(int &k,int a[]){
        scanf("%d",&k);
        for(int i=0;i<k;++i)scanf("%d",a+i);
    }
    int start(){ int E;scanf("%d",&E);return E; }
    void fetch(int &type,int &num,int a[]){
        char s[10];
        scanf("%s%d",s,&num);
        switch(s[0]){
            case 'P':type=1;break;
            case 'R':type=2;break;
            case 'B':type=3;break;
            case 'A':type=4;
                     for(int i=0;i<num;++i)scanf("%d",a+i);
                     break;
        }
    }
    void pay(int n,int a[]){
        for(int i=0;i<n;++i) printf(i?" %d":"%d",a[i]);
        printf("\n"); fflush(stdout);
    }
    void receive(int ATM){
        printf("%d\n",ATM);
        fflush(stdout);
    }
}
#endif
 
const int XX=64;
int n,m,v[XX],a[XX],k[XX],b[XX][XX];
int ta[XX],ba[XX],NE,IE;
int KD;
LL allsum;
 
void br(int a[],int b[]){ for(int i=0;i<n;++i)a[i]=b[i]; }
 
const int MMM=2999999;
int pev[MMM],sv[MMM],sc[MMM],Z;
 
const int SMALL_NOTE_THRESH=7;
void refreshBKNote(){
    map<int,int> M;
    for(int i=0;i<n;++i)M.insert(make_pair(v[i],a[i]));
    int id=0;
    for(map<int,int>::iterator it=M.begin();it!=M.end();++it)
        v[id]=it->first,a[id]=it->second,++id;
    KD=0;
    while(KD<n && v[KD]<=SMALL_NOTE_THRESH) ++KD;
 
    int mx=v[n-1],cnt=0; pev[0]=0;
    for(int i=1;i<mx;++i){
        while(cnt+1<n && v[cnt+1]<=i)++cnt;
        pev[i]=1+pev[i-v[cnt]];
    }
 
    int RAN=mx+2;
    Z=1; while(Z<RAN)Z<<=1;
    for(int i=0;i<mx;++i) sv[Z+i]=pev[i],sc[Z+i]=i;
    for(int i=Z-1;i>=1;--i){
        int l=i<<1,r=l+1;
        if(sv[l]<=sv[r])sv[i]=sv[l],sc[i]=sc[l];
        else sv[i]=sv[r],sc[i]=sc[r];
    }
}
 
int qry(int l,int r){
    if(l==0)return 0;
    int av=INT_MAX,ac=l;
    for(l+=Z-1,r+=Z+1;l+1<r;l>>=1,r>>=1){
        if(!(l&1) && sv[l|1]<av)av=sv[l|1],ac=sc[l|1];
        if( (r&1) && sv[r-1]<av)av=sv[r-1],ac=sc[r-1];
    }
    return ac;
}
 
int changeGet(int p){
    int rc=0;
    for(int i=n-1;i>=0;--i){
        rc+=p/v[i];
        a[i]+=p/v[i]; p%=v[i];
    }
    return rc;
}
int changeTest(int p){ return p/v[n-1]+pev[p%v[n-1]]; }
 
void atmGet(int p,int x){
    int id=k[x]-1;
    for(int i=n-1;i>=0;--i){
        while(b[x][id]>v[i])--id;
        if(b[x][id]<v[i])continue;
        a[i]+=p/v[i]; p%=v[i];
    }
}
 
const int TRY_THRESH=500;
 
int xa[XX],xb[XX],xc[XX];;
const int TIN=200,REP=1;
void Test_tuihuo(int p){
    br(ba,a);
    double mult=max(p/20.0,10.0);
    for(int i=n-1;i>0 && p>=0;--i){
        int x=min(p/v[i],a[i]);
        a[i]-=x; p-=x*v[i];
    }
    a[0]=ba[0]-p; br(xb,a); int fin=p;
    if(n==1){br(a,ba);return;}
    for(int T=TIN;T>0;--T)
        for(int zz=0;zz<REP;++zz){
            br(xa,a); int ok=0,rp=p;
            for(int i=1;i<n;++i) if(a[i]) xc[ok++]=i;
            if(!ok)break;
            int sel=xc[rand()%ok]; --a[sel]; p-=v[sel];
            while(p<0){
                int i=rand()%(n-1)+1;
                int x=min((-p)/v[i]+(p%v[i]!=0),ba[i]-a[i]);
                a[i]+=x; p+=x*v[i];
            }
            if(p<fin){ fin=p; a[0]=ba[0]-p; br(xb,a); }
            if(!(rp>=p || rand()/double(RAND_MAX) <= exp((rp-p)/(mult*T/TIN))))
                br(a,xa),p=rp;
        }
    br(a,ba);
}
 
const int ALLOW_LC=1;
int smallChange(int p){
    int ip=p;
    int cost1=-1,clc=-1,lc=1;
    for(int Q=0;Q<n;++Q){
        p=ip+v[Q]*lc; br(ba,a);
        for(int i=n-1;i>=0 && p>=0;--i){
            int x=min(p/v[i],a[i]);
            a[i]-=x; p-=x*v[i];
        }
        int tlc,ded=min(lc,ba[Q]-a[Q]);
        tlc=(lc-ded)*v[Q]; a[Q]+=ded;
        if(!p && a[0]>cost1){
            cost1=a[0]; clc=tlc; br(xb,a);
        }
        br(a,ba);
    }
    return clc;
}
int asmallChange(int p,int sslc,int lim=n,int llc=INT_MAX){
    int ip=p;
    int cost1=INT_MAX,clc=-1,cost2=-1;
    for(int Q=0;Q<lim;++Q)
        for(int lc=2;lc<=sslc;++lc){
            p=ip+v[Q]*lc; br(ba,a);
            for(int i=n-1;i>=0 && p>=0;--i){
                int x=min(p/v[i],a[i]);
                a[i]-=x; p-=x*v[i];
            }
            int tlc,ded=min(lc,ba[Q]-a[Q]);
            tlc=(lc-ded)*v[Q]; a[Q]+=ded;
            int cc=changeTest(tlc);
            if((lc-ded)<=llc && !p && (cc<cost1||(cc==cost1 && a[0]>cost2))){
                cost1=cc;
                cost2=a[0];
                clc=tlc; br(xb,a);
            }
            br(a,ba);
        }
    int CHANGE_THRESH;
    if(IE<=100)CHANGE_THRESH=2;
    else if(IE<=1000)CHANGE_THRESH=2;
    else CHANGE_THRESH=10;
    if(cost1>CHANGE_THRESH)return -1;
    return clc;
}
 
int runPay_Final(int p){
    for(int i=n-1;i>=0 && p>=0;--i){
        int x=min(p/v[i],a[i]);
        a[i]-=x; p-=x*v[i];
    }
    if(p==0)return -p;
    int em=INT_MAX,es=-1,ec,ed,ex;
    for(int i=1;i<n;++i)
        for(int j=1;j<=TRY_THRESH && j<=a[i];++j){
            if(v[i]*j<p)continue;
            int exces=v[i]*j-p;
            int presv=exces/v[n-1]*v[n-1];
            exces=exces-presv;
            int exd1=min(exces,ba[0]-a[0]);
            int le=exces-exd1;
            int lq=qry(le,exces);
            exd1=exces-lq; exces-=exd1;
            int ez=changeTest(exces+presv);
            if(ez<em || (ez==em && exd1>=ed))
                em=ez,es=i,ec=j,ed=exd1,ex=exces+presv;
        }
    if(~es){
        a[0]+=ed; a[es]-=ec;
        return ex;
    }
    exit(EXIT_FAILURE);
}
 
LL smallSum;
void smallCheck(){
    smallSum=0;
    for(int i=0;i<KD;++i) smallSum+=a[i]*v[i];
}
 
void minimizeC1(int a[],int ba[]){
    for(int i=n-1;i>0;--i){
        int ddd=ba[0]-a[0];
        int x=min(a[i],ddd/v[i]);
        a[0]+=x*v[i]; a[i]-=x;
    }
}
 
const int ZZZ=2048;
int f[XX][ZZZ],pre[XX][ZZZ];
int verySmall(int p){
    int lim=2*p,lic=50,INF=INT_MAX/2;
    for(int j=0;j<=lim;++j)f[0][j]=INF;f[0][0]=0;
    for(int i=0;i<n;++i)
        for(int j=0;j<=lim;++j){
            f[i+1][j]=INF;
            for(int c=0;c<=lic && c<=a[i];++c){
                int co=c*v[i];
                if(co>j)break;
                if(c+f[i][j-co]<f[i+1][j])
                    f[i+1][j]=c+f[i][j-co],pre[i+1][j]=c;
            }
        }
    int ansv,ac=INT_MAX,ax=INT_MAX;
    for(int i=p;i<=lim;++i){
        int ch=changeTest(i-p);
        if(f[n][i]<INF && (ch<ac || (ch==ac&&f[n][i]<ax))){
            ax=f[n][i];
            ac=ch; ansv=i;
        }
    }
    if(ac==INT_MAX)return(-1);
    int et=ansv-p;
    for(int i=n-1;i>=0;--i){
        xb[i]=a[i]-pre[i+1][ansv];
        ansv-=pre[i+1][ansv]*v[i];
    }
    return et;
}
 
void tryPay(int p){
    smallCheck();
 
    if(p<=1000 && NE<10){
        int ec=verySmall(p);
        if(ec>=0){
            minimizeC1(xb,a);
            for(int i=0;i<n;++i)ta[i]=a[i]-xb[i];
            br(a,xb); interactivity::pay(n,ta);
            changeGet(ec);
            return;
        }
    }
 
    int clc=-1;
    if(smallSum<v[n-1]){
        clc=smallChange(p);
        if(clc>=0){
            minimizeC1(xb,a);
            for(int i=0;i<n;++i)ta[i]=a[i]-xb[i];
            br(a,xb); interactivity::pay(n,ta);
            changeGet(clc);
            return;
        }
    }
 
    if(smallSum<v[n-1]){
        clc=asmallChange(p,5,n);
        if(clc>=0){
            minimizeC1(xb,a);
            for(int i=0;i<n;++i)ta[i]=a[i]-xb[i];
            br(a,xb); interactivity::pay(n,ta);
            changeGet(clc);
            return;
        }
    }
 
    if(p>v[n-1]/2.0){
        Test_tuihuo(p);
        if(xb[0]>=0){
            minimizeC1(xb,a);
            for(int i=0;i<n;++i)ta[i]=a[i]-xb[i];
            br(a,xb); interactivity::pay(n,ta);
            return;
        }
    }
 
    br(ba,a);
    int et=runPay_Final(p);
    minimizeC1(a,ba);
    for(int i=0;i<n;++i)ta[i]=ba[i]-a[i];
    interactivity::pay(n,ta);
    changeGet(et);
}
 
double sqr(double x){return x*x;}
double atmEvaluation(){
    double ans=0.0;
    int factor1=IE>1000?15:8;
    for(int i=0;i<n;++i){
        ans+=i?a[i]*factor1:a[i];
    }
    return ans;
}
 
void tryAtm(int p){
    br(ba,a);
    int sm=0;
    double maxeva=-1.0/0.0;
    for(int i=0;i<m;++i){
        atmGet(p,i);
        double ev=atmEvaluation();
        if(ev>maxeva)maxeva=ev,sm=i;
        br(a,ba);
    }
    interactivity::receive(sm+1);
    atmGet(p,sm);
}
 
 
int main() {
    interactivity::init(n,m,v,a); refreshBKNote();
    srand(n*20+m+2); //usability[1]=1;
    for(int i=0;i<m;++i){
        interactivity::iatm(k[i],b[i]);
        sort(b[i],b[i]+k[i]);
    }
    allsum=0;for(int i=0;i<n;++i)allsum+=LL(a[i])*v[i];
 
    IE=NE=interactivity::start();
    while(NE--){
        int tt,p; interactivity::fetch(tt,p,ta);
        switch(tt){
            case 1:tryPay(p);allsum-=p;break;
            case 2:tryAtm(p);allsum+=p;break;
            case 3:a[n]=0;
                   v[n]=p;++n;
                   refreshBKNote();break;
            case 4:k[m]=p;
                   for(int i=0;i<p;++i)b[m][i]=ta[i];
                   sort(b[m],b[m]+k[m]); ++m; break;
        }
    }
}