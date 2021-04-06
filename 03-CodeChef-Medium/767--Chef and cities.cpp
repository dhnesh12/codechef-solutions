#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
///Welcome to Nasif's Code
#define bug printf("bug\n");
#define bug2(var) cout<<#var<<" "<<var<<endl;
#define co(q) cout<<q<<endl;
#define all(q) (q).begin(),(q).end()
#define pi acos(-1)
#define inf 1000000000000000LL
#define FastRead    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define MODADD(ADD_X,ADD_Y)  (ADD_X+ADD_Y)%MOD
#define MODSUB(SUB_X,SUB_Y)  ((SUB_X-SUB_Y)+MOD)%MOD
#define MODMUL(MUL_X,MUL_Y)  (MUL_X*MUL_Y)%MOD
#define LCM(LCM_X,LCM_Y) (LCM_X/__gcd(LCM_X,LCM_Y))*LCM_Y
#define EPS 1e-9
template <typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
typedef long long int ll;
typedef long int li;
typedef unsigned long long int ull;
const int MOD = (int)1e9+7;
const int MAX = 1e6;
int dx[]= {1,0,-1,0,1,-1,1,-1};
int dy[]= {0,1,0,-1,1,-1,-1,1};
li arr[MAX];
long double lg[MAX];
li ans[MAX];
long double lgans[MAX];

li gcd_ext( li a, li m, li &x, li &y)
{
    if( a== 0)
    {
        x= 0;
        y= -1;
        return m;
    }

    li x1, y1, g;

    g= gcd_ext( m% a, a, x1, y1);

    x= -1* y1- (m/ a)* x1;
    y= -1* x1;

    return g;
}

li inv( li a, li m)
{
    li x, y, g;

    g= gcd_ext( a, m, x, y);

    return (x+ m)% m;
}

int main()
{

    //freopen("output.txt", "w", stdout);

        int n,q;
        scanf("%d",&n);
        for(int i=0; i<n; i++)
        {
            scanf("%ld",&arr[i]);
            lg[i]=log10(arr[i]);
        }
        int mn=min(300,n);
        for(int i=1; i<=n; i++)
        {
            ans[i]=1;
            lgans[i]=0.0;
            for(int j=0; j<n; j+=i)
            {
                ans[i]=(ans[i]*arr[j])%MOD;
                lgans[i]+=lg[j];
            }
            lgans[i]+=EPS;
        }
        scanf("%d",&q);
        while(q--)
        {
            int type;
            scanf("%d",&type);
            if(type==1)
            {
                li idx,val;
                scanf("%ld %ld",&idx,&val);
                idx--;

                long double lgval=log10(val);
                li invr=inv(arr[idx],MOD);

                for(int i=1; i<=mn; i++)
                {

                    if(i>idx && idx)
                        break;
                    if(idx%i==0)
                    {
                        ans[i]=1ll*ans[i]*invr%MOD;
                        ans[i]=1ll*ans[i]*val%MOD;

                        lgans[i]=lgans[i]-lg[idx]+lgval;

                    }
                }
                arr[idx]=val;
                lg[idx]=lgval;
            }
            else
            {
                int r;
                scanf("%d",&r);
                if(r<=mn)
                {
                    li tmp=lgans[r];
                    long double fp=lgans[r]-tmp;
                    li dg=(li)(pow(10.0,(fp+EPS)));
                    printf("%ld %ld\n",dg,ans[r]);
                }
                else
                {
                    long double fp=0.0;
                    li res=1;
                    for(int i=0;i<n;i+=r){
                        res=(res*arr[i])%MOD;
                        fp+=lgans[i];
                    }
                    fp+=EPS;
                    fp=(fp-(long int)fp);
                    li dg=(li)(pow(10.0,(fp+EPS)));
                    printf("%ld %ld\n",dg,res);
                }
            }
        }


    return 0;
}
