#include<bits/stdc++.h>
using namespace std;
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define pb push_back
#define mp make_pair
typedef long double ld;
typedef long long ll;
typedef pair<ll,ll> pp;
const ll N = 1000005;
const ll mod  = 4294967296;

ll ans0[40];
ll pow9[40],pow_10[40];
ll pow2[55],pow3[37],pow5[19],pow7[19];

int g2[10]={0,0,1,0,2,0,1,0,3,0};
int g3[10]={0,0,0,1,0,0,1,0,0,2};
int g5[10]={0,0,0,0,0,1,0,0,0,0};
int g7[10]={0,0,0,0,0,0,0,1,0,0};

ll dp[2][2*54 + 1][2*36 + 1][2*18 + 1][2*18 + 1];

int N2=54;
int N3=36;
int N5=18;
int N7=18;

vector<pp> ANS[37];

void print(int x){
    for(auto it:ANS[x])
        cout<<(it.first)<<" "<<it.second<<endl;
}

void fun(){
    pow9[0]=1;
    pow_10[0]=1;

    for(int i=1;i<=36;i++)
    {
        pow9[i] = (1LL*pow9[i-1]*9)%mod;
        pow_10[i] = (1LL*pow_10[i-1]*10)%mod;
        int x = floor((i-1)/2);
        ans0[i] = (1LL*(pow9[i-x]%mod)*(pow_10[x]-pow9[x]+mod)%mod + mod)%mod;
    }
}

void calculate(){

    pow2[0]=1;
    for(int i=1;i<=N2;i++)
        pow2[i] = 1LL*2*pow2[i-1];
    
    pow3[0]=1;
    for(int i=1;i<=N3;i++)
        pow3[i] = 1LL*3*pow3[i-1];

    pow5[0]=1;
    for(int i=1;i<=N5;i++)
        pow5[i] = 1LL*5*pow5[i-1];
    
    pow7[0]=1;
    for(int i=1;i<=N5;i++)
        pow7[i] = 1LL*7*pow7[i-1];


    memset(dp[0],0,sizeof(dp[0]));

    dp[0][N2][N3][N5][N7]=1;

    int p=1;

    for(int L=1;L<=36;L++)
    {

        memset(dp[p],0,sizeof(dp[p]));

        int even_pos = (L-1)/2;
        int odd_pos = (L-1)-even_pos;

        // cout<<L<<" "<<even_pos<<" "<<odd_pos<<endl<<endl;

        for(int n2 = -3*even_pos;n2<= 3*odd_pos;n2++)
        {
            for(int n3 = -2*even_pos;n3<= 2*odd_pos;n3++)
            {
                for(int n5 = -1*even_pos;n5<= 1*odd_pos;n5++)
                {
                    for(int n7 = -1*even_pos;n7<= 1*odd_pos;n7++)
                    {
                        // cout<<n2<<" "<<n3<<" "<<n5<<" "<<n7<<endl;

                        ll ans = dp[!p][N2+n2][N3+n3][N5+n5][N7+n7];
                        if(ans>0){
                        for(int d=1;d<=9;d++){
                            dp[p][N2+g2[d]-n2][N3+g3[d]-n3][N5+g5[d]-n5][N7+g7[d]-n7] = (dp[p][N2+g2[d]-n2][N3+g3[d]-n3][N5+g5[d]-n5][N7+g7[d]-n7]+ans)%mod;
                        }    
                        }
                    }
                }
            }    
        }

        odd_pos = (L+1)/2;

        for(int n2=0;n2<=3*odd_pos;n2++){
            for(int n3=0;n3<=2*odd_pos;n3++){
                for(int n5=0;n5<=odd_pos;n5++){
                    for(int n7=0;n7<=odd_pos;n7++)
                    {
                        ll ans = dp[p][N2+n2][N3+n3][N5+n5][N7+n7];
                        if(ans>0)
                        {
                            ll v = 1LL*pow2[n2]*pow3[n3]*pow5[n5]*pow7[n7];
                            if(v<1000000000000000000)
                                ANS[L].pb(mp(v,ans));
                        }
                        
                    }
                }
            }
        }


        if(p==0)
            p=1;
        else
            p=0;


        sort(ANS[L].begin(),ANS[L].end());
    }

    
}


void solve(){
    ll l,v,n,n2,n3,n5,n7;
    int t;
    cin>>t;

    while(t--)
    {
        cin>>l>>v;
        if(v==0){
            cout<<ans0[l]<<endl;
        }
        else
        {
            
            int pos = lower_bound(ANS[l].begin(),ANS[l].end(),mp(v,1LL*0))-ANS[l].begin();
            // int pos = 0;
            ll ans = 0;
            if(pos<ANS[l].size() && ANS[l][pos].first==v){
                ans = ANS[l][pos].second;
            }

            cout<<ans%mod<<endl;
        }

    }
}    


   
int main()
{
    FAST
        

    fun(); 
    calculate();   
    solve();
    
    return 0;
}