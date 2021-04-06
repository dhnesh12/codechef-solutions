#include <bits/stdc++.h>
#define LL long long
#define PII pair<int,int>
#define PIL pair<int,LL>
#define PLI pair<LL,int>
#define PIII pair<int,PII>
#define PLL pair<LL,LL>
#define PLII pair<LL,PII>
#define VI vector<int>
#define VVI vector<VI>
#define VL vector<LL>
#define VVL vector<VL>
#define VPII vector<PII>
#define FF first
#define SS second
#define MP make_pair
#define PB push_back
#define all(x) x.begin(),x.end()
#define watch(x) cout<<(#x)<<" = "<<(x)<<'\n'
#define mset(a,v) memset(a,v,sizeof(a))
#define setp(x) cout<<fixed<<setprecision(x)
#define EPS 0.00000000001
#define PI acos(-1)
#define loop(i,b,n) for(int i=b;i<n;++i)
#define rev_loop(i,b,n) for(int i=b;i>=n;--i)
using namespace std;

const int MOD = 1e9 + 7;
const LL MX = 50;
const LL INF = 1e9;

int gn[MX][MX], v[MX][MX];

void cal(int b, int e)
{
    int f[MX] = {0};

    loop(i,b,e+1)
    {
        loop(j,i,e+1)
        {
            if(v[i][j] == 0) continue;

            int g = 0;

            if(i != b)
            {
                if(gn[b][i-1] == -1) cal(b,i-1);
                g = gn[b][i-1];
            }

            if(j != e)
            {
                if(gn[j+1][e] == -1) cal(j+1,e);
                g ^= gn[j+1][e];
            }

            f[g] = 1;
        }
    }

    loop(i,0,MX) if(f[i] == 0) {gn[b][e] = i; break;}
}

int main()
{
    //ofstream out("output.txt");
    //ifstream in("input.txt");
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

    int t, n;
    string w, s[MX];
    cin>>t;

    while(t--)
    {
        cin>>w>>n;
        loop(i,0,n) cin>>s[i];

        mset(v,0);
        int l = w.length();

        loop(i,0,n)
        {
            loop(j,0,l)
            {
                int id = j;

                for(char ch : s[i])
                {
                    if(id < l && ch == w[id]) ++id;
                    else {id = -1; break;}
                }

                if(id != -1) v[j][id-1] = 1;
            }
        }

        mset(gn,-1);
        cal(0,l-1);

        if(gn[0][l-1]) cout<<"Teddy\n";
        else cout<<"Tracy\n";

    }

    return 0;
}
