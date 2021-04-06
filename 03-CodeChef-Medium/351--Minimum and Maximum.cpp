///****In the name of ALLAH, most Gracious, most Compassionate****//

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair <int, int> pii;

#define ALL(a) a.begin(), a.end()
#define FastIO ios::sync_with_stdio(false); cin.tie(0);cout.tie(0)
#define IN freopen("input.txt","r+",stdin)
#define OUT freopen("output.txt","w+",stdout)

#define DBG(a) cerr<< "line "<<__LINE__ <<" : "<< #a <<" --> "<<(a)<<endl
#define NL cout<<endl

template < class T1,class T2>
ostream &operator <<(ostream &os,const pair < T1,T2 > &p)
{
    os<<"{"<<p.first<<","<<p.second<<"}";
    return os;
}

const int N=3e5+5;
const int oo=1e9+7;

int cntA[N<<2]; // min
int cntB[N<<2]; // max
int sum[N];

void combine(int u)
{
    cntA[u] = cntA[u<<1]+cntA[u<<1|1];
    cntB[u] = cntB[u<<1]+cntB[u<<1|1];
    sum[u]  = sum[u<<1] +sum[u<<1|1] ;
}

void propagate(int u,int ss,int se)
{
    if(ss!=se)
    {
        if(cntA[u] == 0 )
            cntA[u<<1] = 0,
                         cntA[u<<1|1] = 0;
        if(cntB[u] == 0 )
            cntB[u<<1] = 0,
                         cntB[u<<1|1] = 0;

        int mid= (ss+se)/2;

        if(cntA[u]== se-ss+1)
            cntA[u<<1] = mid-ss+1,
                         cntA[u<<1|1] = se-mid;
        if(cntB[u]== se-ss+1)
            cntB[u<<1] = mid-ss+1,
                         cntB[u<<1|1] = se-mid;
    }
    if(cntA[u]==0 or cntB[u]==0)
        sum[u] = 0;
    else if(cntA[u]== se-ss+1 )
        sum[u] =cntB[u];
    else if(cntB[u] == se-ss+1)
        sum[u] =cntA[u];
}

void updateA(int u,int ss,int se,int qs,int qe,int x)
{
    propagate(u,ss,se);
    if(qe < ss or se < qs)
        return ;
    if(qs<=ss and se<= qe)
    {
        if(x)
            cntA[u] = se-ss+1;
        else
            cntA[u] =0;
        return propagate(u,ss,se);
    }
    int mid = (ss+se)/2;
    updateA(u<<1, ss, mid,qs,qe,x);
    updateA(u<<1|1, mid+1,se,qs,qe,x);
    combine(u);
}
void updateB(int u,int ss,int se,int qs,int qe,int x)
{
    propagate(u,ss,se);
    if(qe < ss or se < qs)
        return ;
    if(qs<=ss and se<= qe)
    {
        if(x)
            cntB[u] = se-ss+1;
        else
            cntB[u] =0;
        return propagate(u,ss,se);
    }
    int mid = (ss+se)/2;
    updateB(u<<1, ss, mid,qs,qe,x);
    updateB(u<<1|1, mid+1,se,qs,qe,x);
    combine(u);
}


int query(int u,int ss,int se,int qs,int qe)
{
    propagate(u,ss,se);
    if(qe< ss or se < qs)
        return 0;
    if(qs<=ss and se<= qe )
        return sum[u];
    int mid  = (ss+se)/2;
    return  query(u<<1,ss,mid,qs,qe) + query(u<<1|1, mid+1, se, qs, qe) ;
}

int p[N];


int32_t main()
{
    FastIO;

    int T,cs=0;
    cin>>T;
    while(T--)
    {
        int n;
        cin>>n;
        for(int i=1;i<=n;i++)
        {
            cin>>p[i];
        }
        ll ans  = 0;
        for(int bit = 0; (1<<bit )<= n ;bit++)
        {
            updateA(1,1,n,1,n,0);
            updateB(1,1,n,1,n,0);
            stack<int > mn,mx;
            for(int i=1;i<=n;i++)
            {
                while(!mn.empty() and p[mn.top()] < p[i]) mn.pop();
                while(!mx.empty() and p[mx.top()] > p[i]) mx.pop();

                bool val = p[i] & (1<<bit);

                {
                    int lastmaxindex = mn.empty() ? 1 : mn.top() + 1;
                    updateB(1 , 1 ,n ,lastmaxindex , i, val);
                }
                {
                    int lastminindex = mx.empty() ? 1 : mx.top() + 1;
                    updateA(1 , 1 ,n ,lastminindex , i, val);
                }

                mn.push(i);
                mx.push(i);

                ans+=(1LL<<bit) * query(1,1,n,1,n);

            }
        }

        cout<<ans<<"\n";
    }
}
