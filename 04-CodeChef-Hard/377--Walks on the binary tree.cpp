#include <cstdio>
#include <cctype>
#include <cstring>
#include <set>
using namespace std;
typedef unsigned long long llu;

const int P=912881939;
struct HashNode{
    llu a,b;
    HashNode(void){}
    HashNode(const llu &x):a(x%P),b(x){}
    HashNode(const llu &a_,const llu &b_):a(a_),b(b_){}
}B[100001];
inline bool operator == (const HashNode &a,const HashNode &b){return a.a==b.a && a.b==b.b;}
inline bool operator != (const HashNode &a,const HashNode &b){return a.a!=b.a || a.b!=b.b;}
inline HashNode operator + (const HashNode &a,const HashNode &b){return HashNode(a.a+b.a<P?a.a+b.a:a.a+b.a-P,a.b+b.b);}
inline HashNode operator * (const HashNode &a,const HashNode &b){return HashNode(a.a*b.a%P,a.b*b.b);}

int T,n,Q,c,i,j;

int a[100001];
struct SegT{
    int lc,rc;
    HashNode v0,v1;
}t[20000005];
int tot,rt[100001];
#define mid ((l_+r_)>>1)
void Build(int &p,int l_,int r_){
    p=++tot;
    if(l_==r_)
        return (void)(t[p].v0=1,t[p].v1=2);
    Build(t[p].lc,l_,mid);
    Build(t[p].rc,mid+1,r_);
    t[p].v0=t[t[p].lc].v0*B[r_-mid]+t[t[p].rc].v0;
    t[p].v1=t[t[p].lc].v1*B[r_-mid]+t[t[p].rc].v1;
    return;
}
int Flip(int p,int x,int l_,int r_){
    int q=++tot;
    t[q]=t[p];
    if(l_==r_)
        return swap(t[q].v0,t[q].v1),q;
    x<=mid?(t[q].lc=Flip(t[p].lc,x,l_,mid)):(t[q].rc=Flip(t[p].rc,x,mid+1,r_));
    t[q].v0=t[t[q].lc].v0*B[r_-mid]+t[t[q].rc].v0;
    t[q].v1=t[t[q].lc].v1*B[r_-mid]+t[t[q].rc].v1;
    return q;
}
int Comp(int p,int q,int l_,int r_){
    if(l_==r_)
        return (t[p].v0==2)-(t[q].v0==2);
    return t[t[p].lc].v0!=t[t[q].lc].v0?Comp(t[p].lc,t[q].lc,l_,mid):Comp(t[p].rc,t[q].rc,mid+1,r_);
}
int Lcp(int p,int q,int l_,int r_){
    if(l_==r_)
        return t[p].v0==t[q].v0;
    return t[t[p].lc].v0!=t[t[q].lc].v0?Lcp(t[p].lc,t[q].lc,l_,mid):mid-l_+1+Lcp(t[p].rc,t[q].rc,mid+1,r_);
}
#undef mid

llu ans;
struct Num{
    int x;
    Num(void){}
    Num(const int &x_):x(x_){}
};
inline bool operator <(const Num &i,const Num &j){return Comp(rt[i.x],rt[j.x],1,n)<0;}
set<Num> st;
set<Num>::iterator it;

int main(){
    B[0]=1,B[1]=131;
    for(int i=2;i<=100000;++i)
        B[i]=B[i-1]*B[1];
    scanf("%d",&T);
    int op;
    while(T--){
        tot=0;
        st.clear();
        i=0;
        ans=1;
        scanf("%d%d",&n,&Q);
        memset(a+1,0,sizeof(int)*n);
        Build(rt[0],1,n);
        while(Q--){
            while(isspace(op=getchar()));
            switch(op){
                case '!':{
                    scanf("%d",&c),c=n-c;
                    ++i;
                    rt[i]=rt[i-1];
                    for(j=c;j && a[j];--j)
                        a[j]^=1,rt[i]=Flip(rt[i],j,1,n);
                    if(j)
                        a[j]^=1,rt[i]=Flip(rt[i],j,1,n);
                    Num ni(i);
                    if(st.size()){
                        it=st.lower_bound(ni);
                        if(it!=st.end()){
                            if(Comp(rt[i],rt[it->x],1,n)){
                                int x=it->x;
                                ans+=n;
                                ans-=Lcp(rt[i],rt[it->x],1,n);
                                if(it!=st.begin()){
                                    --it;
                                    ans+=Lcp(rt[x],rt[it->x],1,n);
                                    ans-=Lcp(rt[i],rt[it->x],1,n);
                                }
                            }
                        }else{
                            --it;
                            ans+=n;
                            ans-=Lcp(rt[i],rt[it->x],1,n);
                        }
                    }else{
                        ans=n+1;
                    }
                    st.insert(ni);
                }
                break;
                case '?':{
                    printf("%llu\n",ans);
                }
                break;
            }
        }
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}