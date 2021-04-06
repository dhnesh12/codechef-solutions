    #include<iostream>
    #include<cstdio>
    #include<cstring>
    #include<cstdlib>
    #include<map>
    #include<vector>
    #include<list>
    #include<set>
    #include<queue>
    #include<cassert>
    #include<sstream>
    #include<string>
    #include<cmath>
    #include<algorithm>
    using namespace std;
    #define LET(x,a) __typeof(a) x(a)
    #define IFOR(i,a,b) for(LET(i,a);i!=(b);++i)
    #define EACH(it,v) IFOR(it,v.begin(),v.end())
    #define FOR(i,a,b) for(int i=(int)(a) ; i < (int)(b);++i)
    #define REP(i,n) FOR(i,0,n)
    #define PB push_back
    #define MP make_pair
    #define EPS 1e-9
    #define INF 2000000000
    typedef vector<int> VI;
    typedef long long LL;
    typedef pair<int,int> PI;
    int n,m;
    int path[100005][2],index1;
    void print(int x1,int y1,int x2,int y2,int s1,int s2){
    for(;x1!=x2 || y1!=y2;y1+=s2){
    path[index1][0]=x1;
    path[index1][1]=y1;
    index1++;
    x1+=s1;
    }
    path[index1][0]=x2;
    path[index1++][1]=y2;
    return;
    }
    void findAndPrint(int x,int y){
    int st = -1;
    REP(i,index1)if(path[i][0]==x && path[i][1]==y){
    st=i;
    break;
    }
    assert(st!=-1);
    int cur = st;
    REP(len,index1+1){
    printf("%d %d\n",path[cur][0],path[cur][1]);
    cur++;
    if(cur==index1)cur=0;
    }
    return;
    }
    int main(){
    int t;cin>>t;
    assert(t<=100);
    while(t--){
    scanf("%d%d",&n,&m);
    assert(n*m>1 && n*m<=100000);
    int G[n+1][m+1];
    int sum1 = 0, sum2 = 0;
    index1=0;
    REP(i,n)REP(j,m){
    int tmp;
    scanf("%d",&G[i][j]);
    assert(G[i][j]>=0 && G[i][j]<=10000);
    if((i+j)&1)sum2+=G[i][j];
    else sum1 += G[i][j];
    }
    if(n==1 || m==1) {
    // The only gain is the only neighbor of starting point
    if(n==1){
    cout<<max(G[0][1],G[0][m-2])<<endl;
    if(G[0][1]>=G[0][m-2])cout<<"3\n0 0\n0 1\n0 0\n";
    else printf("3\n0 %d\n0 %d\n0 %d\n",m-1,m-2,m-1);
    }
    else {
    cout<<max(G[1][0],G[n-2][0])<<endl;
    if(G[1][0]>=G[n-2][0])cout<<"3\n0 0\n1 0\n0 0\n";
    else printf("3\n%d 0\n%d 0\n%d 0\n",n-1,n-2,n-1);
    }
    }
    else if(n%2==0 || m%2==0){
    // find the cycle.
    if(m%2==0){
    print(0,0,n-1,0,1,0);
    int c = 1;
    while(c<m){
    if(c&1){
    print(n-1,c,1,c,-1,0);
    }
    else print(1,c,n-1,c,1,0);
    c++;
    }
    print(0,m-1,0,0,0,-1);
    } else {
    print(0,0,0,m-1,0,1);
    int c = 1;
    while(c<n){
    if(c&1){
    print(c,m-1,c,1,0,-1);
    }
    else print(c,1,c,m-1,0,1);
    c++;
    }
    print(n-1,0,0,0,-1,0);
    }
    index1--;
    assert(index1==n*m);
    if(sum2>=sum1){
    printf("%d\n%d\n",sum2,n*m+1);
    findAndPrint(0,0);
    }
    else {
    printf("%d\n%d\n",sum1,n*m+1);
    if(n%2==0)findAndPrint(n-1,0);
    else findAndPrint(0,m-1);
    }
    }
    else {
    //find the cycle
    print(0,0,n-1,0,1,0);
    int c = n-1;
    while(c!=1){
    if(c&1){
    print(c,m-1,c,1,0,-1);
    }
    else {
    print(c,1,c,m-1,0,1);
    }
    c--;
    }
    c = m-1;
    int r = 1;
    while(c!=0){
    print(r,c,r,c-1,0,-1);
    c--;
    r = 1-r;
    }
    index1--;
    assert(index1==n*m-1);
    printf("%d\n%d\n",sum2,n*m);
    findAndPrint(0,0);
    }
    }
    return 0;
    }  