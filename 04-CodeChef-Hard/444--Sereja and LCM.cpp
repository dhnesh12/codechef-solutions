#include<bits/stdc++.h>
using namespace std;
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define memo(a,v) memset(a,v,sizeof(a))
#define pb push_back
#define all(a) a.begin(),a.end()
#define eps (1e-9)
#define inf (1<<29)
#define i64 long long
#define u64 unsigned i64
#define AIN(a,b,c) assert(a<=b && b<=c)
#define MAXN 1000000000
#define MAX 500
#define MOD 1000000007
#define hell 1000000007
#define int long long
#define matrix vector< vector<int> >
typedef pair<int,int> pii;

//Dp[n][mask]=sum(C[i][mask]*Dp[n-1][i] for i=0 to 1<<p )
//All transitions of dp[n,x] are dependent on dp[n-1,y] not on dp[n,z]

//[dp[n][0],1,2,...,2^k-1]=[C[0][0],C[1][0],C[2][0],...,C[2^k-1][0]][Dp[n-1][0]
                                                                //   Dp[n-1][1]
                                                                //   Dp[n-1][2]
                                                                //   Dp[n-1][3]
                                                                //    ....
                                                                //   Dp[n-1][2^k-1]       ]


// =[]

int t1=MAX;

matrix matmul(matrix &a, matrix &b){
    int i, j, k, n = a.size();
    matrix ans (n, vector<int>(n));
    for(i=0;i<n;i++)
        for(j=0;j<n;j++){
            int temp = 0;
            for(k=0;k<n;k++)    temp = (temp + a[i][k] * b[k][j]) % hell;
            ans[i][j] = temp;
        }
 
    return ans;
}
 
matrix matpwr(matrix &a, int p){
    int n = a.size();
    matrix ans(n, vector<int> (n));
    for(int i=0;i<n;i++)    ans[i][i] = 1;
 
    while(p){
        if(p&1) ans = matmul(ans, a);
 
        a = matmul(a, a);
        p >>= 1;
    }
    return ans;
}


int mat[502][502],res[1][502],temp[1][502],mat1[502][502];
vector<int> pf, cnt;
 main(){
    int t, n, k, i,m, L, R, d, j, p, c, mask, nmask;
    //scanf("%d",&t);
    cin>>t;
    //AIN(1,t,10);
    while(t--){
        //scanf("%d %d %d %d",&n,&m,&L,&R);
        cin>>n>>m>>L>>R;
      //  AIN(1,n,5000000);
        //AIN(1,L,R);
        //AIN(L,R,m);
        // AIN(R,m,1000);
        int ans = 0;
        
        for(d = L;d<=R;d++){
            int k = d;
            pf.clear();
            cnt.clear();
            for(i = 2;i*i<=k;i++){
                if(k % i) continue;
                c = 0;
                while(k%i==0){
                    k/=i;
                    c++;
                }
                pf.pb(i);
                cnt.pb(c);
            }
            if(k>1){
                pf.pb(k);
                cnt.pb(1);
            }
            int p = pf.size();
            int t1=1<<p;
            

            for(i=0;i<t1;i++)
                for(j=0;j<t1;j++)
                    mat[i][j]=0,mat1[i][j]=0;

            for(i=0;i<t1;i++)
                res[0][i]=0,temp[0][i]=0;

            // memset(mat,0,sizeof(mat));
            // memset(res,0,sizeof(res));

            for(mask = 0;mask < (1<<p);mask++){
                for(i = 1;i<=m;i++){
                    nmask = mask;
                    for(j = 0;j<p;j++){
                        k = i;
                        c = 0;
                        while(k%pf[j]==0)
                        {
                            k/=pf[j];
                            c++;
                        }
                        if(c>=cnt[j]){
                            nmask |= (1<<j);
                        }
                    }
                    mat[mask][nmask]++;
                  //  mat1[mask][nmask]++;
                    //No. of ways to reach nmask from mask.

                }
            }
            k=1<<p;
             matrix M(k,vector<int>(k));
             
             for(i=0;i<(k);i++)
                for(j=0;j<k;j++)
                    M[i][j]=mat[i][j];
            
            matrix ans3=matpwr(M,n);
            // for(i=0;i<k;i++)
            // for(j=0;j<k;j++)
            // cout<<
           

        
            //int ans1=mat[0][(1<<p)-1];
             ans+= ans3[0][k-1];
             ans%=MOD;
        }
        cout<<ans<<"\n";
        // printf("%d\n",ans);
    }
 //   AIN (1, cnt, 500000);
  return 0;
}
