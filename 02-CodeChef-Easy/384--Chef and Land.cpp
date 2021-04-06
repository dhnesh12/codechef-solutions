#include<bits/stdc++.h>
using namespace std;

#define inf 1001000009
#define infmx 1e18
#define ff first
#define ss second
#define ll long long
#define pb push_back
#define MP make_pair
#define IOS ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL)
#define all(x) x.begin(),x.end()
///debug
#define wh(x)   cerr<<#x<<" is "<<x<<endl;
#define error(args...){string _s=#args;replace(_s.begin(),_s.end(),',',' ');stringstream _ss(_s);istream_iterator<string> _it(_ss);err(_it,args);}
void err(istream_iterator<string>it){cout<<endl;}
template<class H,class... T>void err(istream_iterator<string>it,H a,T... t){cerr<<*it<<" = "<<a<<" | ";err(++it,t...);}
template<class S,class T>ostream&operator<<(ostream&os,pair<S,T>p){os<<"["<<p.first<<", "<<p.second<<"]";return os;};
template<class T>auto&operator<<(ostream& os,vector<T>_v){bool a=1;for(auto x:_v){os<<(a?"":" ")<<x;a=0;}return os;}
///
typedef pair<int,int>pi;
typedef pair<long long,long long>pll;
typedef pair<pi,int>ppi;
typedef pair<int,pi>pip;
typedef vector<int>vi;
typedef vector<pi>vpi;
const int mod=1e9+7;
ll power(ll a,ll p){ll r=1,y=a;while(p){if(p&1)r=(1LL*r*y)%mod;p>>=1;y=(1LL*y*y)%mod;}return r;}

const int N=210;
char ara[N][N];
int n,m;
int fx[]={0,0,1,-1};
int fy[]={1,-1,0,0};
int path[N][N];
bool vis[N][N];
string ans;
string tp="LRUD";
void bfs(int sx,int sy)
{
    queue<pi>q;
    q.push(MP(sx,sy));
    vis[sx][sy]=1;
    path[sx][sy]=-1;
    while(!q.empty())
    {
        int x,y;
        tie(x,y)=q.front();
        q.pop();
        for(int k=0;k<4;k++)
        {
            int xx=x+fx[k],yy=y+fy[k];
            if(xx>=0&&xx<n&&yy>=0&&yy<m){
                if(ara[xx][yy]=='.'&&vis[xx][yy]==0)
                {
                    q.push(MP(xx,yy));
                    path[xx][yy]=k;
                    vis[xx][yy]=1;
                }
            }
        }
    }
//    for(int i=0;i<n;i++){
//        for(int j=0;j<m;j++)
//            cout<<path[i][j];
//        cout<<endl;
//    }
}
pi get_pos(int x,int y)
{
    for(auto p:ans){
        if(p=='R'&&(y+1)<m&&ara[x][y+1]=='.')y++;
        else if(p=='L'&&(y-1)>=0&&ara[x][y-1]=='.')y--;
        else if(p=='U'&&(x-1)>=0&&ara[x-1][y]=='.')x--;
        else if(p=='D'&&(x+1)<n&&ara[x+1][y]=='.')x++;
    }
    return MP(x,y);
}
void process(int x,int y)
{
    while(ara[x][y]!='C'){
        int k=path[x][y];
        x=x-fx[k];
        y=y-fy[k];
        ans+=tp[k];
    }
}
int main()
{
    IOS;
    cin>>n>>m;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)cin>>ara[i][j];
    int x,y;
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)if(ara[i][j]=='C')x=i,y=j;
    bfs(x,y);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++){
            if(ara[i][j]=='*'||ara[i][j]=='C')continue;
            tie(x,y)=get_pos(i,j);
//            error(i,j,x,y);
            process(x,y);
//            cerr<<ans<<endl;
        }
    }
    cout<<ans<<endl;
}

/*
6 7
*******
*..**.*
*C..*.*
*..**.*
**....*
*******

*/
