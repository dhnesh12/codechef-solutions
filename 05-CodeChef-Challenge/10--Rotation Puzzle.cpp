 #include <cstdio>
    #include <cstdlib>
    #include <cassert>
    #include <cstring>
    #include <queue>
    #include <map>
    using namespace std;
    #define debug(x) fprintf(stderr, "%s %d\n", #x, (int)(x))
    int M, N, grid[34][34];
    int route[10000][3], routelen, flipped;
    char obuf[100000];
    map<unsigned int, int> finalstate[6];
    int f_id[5][5];
    int readint(){
    const static int SIZE=4000;
    static char buf[SIZE];
    static int i=0, n=0;
    int num=0, h=0;
    for(;;){
    if(i==n){
    i=0;
    n=fread(buf, 1, SIZE, stdin);
    if(!n)
    return num;
    }
    int c=buf[i++];
    if('0'<=c && c<='9'){
    num=num*10+c-'0';
    h=1;
    }else if(h)
    return num;
    }
    }
    void readcase(){
    M=readint();
    N=readint();
    for(int i=0; i<M; i++)
    for(int j=0; j<N; j++)
    grid[i][j]=readint()-1;
    }
    void printcase(){
    printf("%d\n", routelen);
    char *ptr=obuf;
    for(int i=0; i<routelen; i++){
    *ptr++='0'+route[i][0];
    *ptr++=' ';
    if(route[i][1]<10){
    *ptr++='0'+route[i][1];
    }else{
    *ptr++='0'+(route[i][1]/10);
    *ptr++='0'+(route[i][1]%10);
    }
    *ptr++=' ';
    if(route[i][2]<10){
    *ptr++='0'+route[i][2];
    }else{
    *ptr++='0'+(route[i][2]/10);
    *ptr++='0'+(route[i][2]%10);
    }
    *ptr++='\n';
    }
    *ptr=0;
    puts(obuf);
    }
    void debuggrid(FILE *f=stderr){
    fprintf(f, "%d %d\n", M, N);
    int len=M*N>=999 ? 4 : M*N>=99 ? 3 : M*N>=9 ? 2 : 1;
    for(int i=0; i<M; i++){
    for(int j=0; j<N; j++)
    fprintf(f, "%*d ", len, grid[i][j]+1);
    fputc('\n', f);
    }
    fputc('\n', f);
    }
    void rot(int c, int i, int j, int add=1){
    assert(routelen<10000);
    assert(i<M-1);
    assert(j<N-1);
    if(c){
    int tmp=grid[i][j];
    grid[i][j]=grid[i+1][j];
    grid[i+1][j]=grid[i+1][j+1];
    grid[i+1][j+1]=grid[i][j+1];
    grid[i][j+1]=tmp;
    }else{
    int tmp=grid[i][j];
    grid[i][j]=grid[i][j+1];
    grid[i][j+1]=grid[i+1][j+1];
    grid[i+1][j+1]=grid[i+1][j];
    grid[i+1][j]=tmp;
    }
    if(add){
    if(!flipped){
    route[routelen][0]=c;
    route[routelen][1]=i+1;
    route[routelen][2]=j+1;
    }else{
    route[routelen][0]=c^1;
    route[routelen][1]=j+1;
    route[routelen][2]=i+1;
    }
    routelen++;
    }
    }
    void flip(){
    if(M<N){
    for(int i=0; i<M; i++)
    for(int j=i+1; j<M; j++){
    int tmp=(grid[i][j]/N)+(grid[i][j]%N)*M;
    grid[i][j]=(grid[j][i]/N)+(grid[j][i]%N)*M;
    grid[j][i]=tmp;
    }
    for(int i=0; i<M; i++)
    grid[i][i]=(grid[i][i]/N)+(grid[i][i]%N)*M;
    for(int i=M; i<N; i++)
    for(int j=0; j<M; j++)
    grid[i][j]=(grid[j][i]/N)+(grid[j][i]%N)*M;
    }else{
    for(int i=0; i<N; i++)
    for(int j=i+1; j<N; j++){
    int tmp=(grid[i][j]/N)+(grid[i][j]%N)*M;
    grid[i][j]=(grid[j][i]/N)+(grid[j][i]%N)*M;
    grid[j][i]=tmp;
    }
    for(int i=0; i<N; i++)
    grid[i][i]=(grid[i][i]/N)+(grid[i][i]%N)*M;
    for(int i=0; i<N; i++)
    for(int j=N; j<M; j++)
    grid[i][j]=(grid[j][i]/N)+(grid[j][i]%N)*M;
    }
    int tmp=M;
    M=N;
    N=tmp;
    flipped^=1;
    }
    inline int abs(int x){
    return x>0 ? x : -x;
    }
    int impr(int i1, int j1, int i2, int j2){
    int ii=grid[i1][j1]/N;
    int jj=grid[i1][j1]%N;
    return abs(i1-ii)+abs(j1-jj)-(abs(i2-ii)+abs(j2-jj));
    }
    int delta(int c, int i, int j){
    int ret=impr(i, j, i, j+1)+impr(i, j+1, i+1, j+1)
    +impr(i+1, j+1, i+1, j)+impr(i+1, j, i, j);
    return c ? ret : -ret;
    }
    unsigned int getfinalstate(int i, int j){
    unsigned int res=0;
    int c=0;
    for(int y=i; y<M; y++)
    for(int x=j; x<N && c<8; x++){
    res|=((grid[y][x]/N-i)*(N-j)+(grid[y][x]%N-j))<<(c<<2);
    c++;
    }
    return res;
    }
    unsigned int getfinalstate0(){
    unsigned int res=0;
    int c=0;
    for(int y=0; y<M; y++)
    for(int x=0; x<N && c<8; x++){
    res|=grid[y][x]<<(c<<2);
    c++;
    }
    return res;
    }
    unsigned int hash[600000];
    int testandset(unsigned int p){
    int s=p%564229;
    while(hash[s]!=p && hash[s])
    s++;
    if(hash[s]==p)
    return 1;
    hash[s]=p;
    return 0;
    }
    void makefinalstate(int m, int n, int id){
    memset(hash, 0, sizeof(hash));
    M=m; N=n;
    f_id[M][N]=id;
    for(int i=0; i<M; i++)
    for(int j=0; j<N; j++)
    grid[i][j]=i*N+j;
    queue<unsigned int> q;
    finalstate[id][getfinalstate0()]=-1;
    testandset(getfinalstate0());
    int unmarked[1<<9];
    for(int i=0; i<9; i++)
    unmarked[((1<<9)-1)^(1<<i)]=i;
    for(q.push(getfinalstate0()); !q.empty(); q.pop()){
    unsigned int f=q.front();
    int c=0;
    int mark=0;
    for(int i=0; i<M; i++)
    for(int j=0; j<N; j++){
    if(c<8){
    grid[i][j]=(f>>(c<<2))&15;
    mark|=1<<grid[i][j];
    c++;
    }else{
    grid[i][j]=unmarked[mark];
    }
    }
    for(int y=0; y<M-1; y++)
    for(int x=0; x<N-1; x++)
    for(int c=0; c<2; c++){
    rot(c^1, y, x, 0);
    unsigned int n=getfinalstate0();
    if(!testandset(n)){
    finalstate[id][n]=(c<<4)|(y<<2)|x;
    q.push(n);
    }
    rot(c, y, x, 0);
    }
    }
    }
    void init(){
    makefinalstate(2,2,0);
    makefinalstate(2,3,1);
    makefinalstate(2,4,2);
    makefinalstate(3,2,3);
    makefinalstate(3,3,4);
    makefinalstate(4,2,5);
    }
    void rotbest(int c1, int y1, int x1, int c2, int y2, int x2){
    int h1=delta(c1, y1, x1);
    int h2=delta(c2, y2, x2);
    if(h1>h2)
    rot(c1, y1, x1);
    else
    rot(c2, y2, x2);
    }
    void solvecolumn(){
    assert(N>=3 && M>=2);
    for(int i=M-1; i>=2; i--){
    int v=i*N+N-1;
    int y=0, x=0;
    while(grid[y][x]!=v){
    x++;
    if(x==N){
    y++;
    x=0;
    if(y==M)
    debuggrid();
    assert(y<M);
    }
    }
    if(0<x && x<N-2)
    for(; y>i; y--)
    rotbest(1, y-1, x, 0, y-1, x-1);
    else if(x==0)
    for(; y>i; y--)
    rot(1, y-1, x);
    else
    for(; y>i; y--)
    rot(0, y-1, x-1);
    if(0<x && x<N-1)
    for(; y<i; y++)
    rotbest(1, y, x-1, 0, y, x);
    else if(x==0)
    for(; y<i; y++)
    rot(0, y, x);
    else
    for(; y<i; y++)
    rot(1, y, x-1);
    if(y==M-1)
    for(; x<N-1; x++)
    rot(0, y-1, x);
    else{
    for(; x<N-2; x++)
    rotbest(0, y-1, x, 1, y, x);
    if(x<N-1){
    rot(0, y-1, x);
    x++;
    }
    }
    assert(grid[i][N-1]==v);
    }
    int v1=N-1, v2=2*N-1;
    if(grid[0][N-1]!=v1 || grid[1][N-1]!=v2){
    if(grid[0][N-1]==v2 && grid[1][N-1]==v1)
    rot(0, 0, N-2);
    if(grid[0][N-1]==v1){
    if(grid[0][N-2]==v2)
    rot(1, 0, N-3);
    rot(1, 0, N-2);
    }
    if(grid[1][N-1]==v2){
    if(grid[1][N-2]==v1)
    rot(0, 0, N-3);
    rot(0, 0, N-2);
    }
    if(grid[0][N-1]==v2){
    int y=0, x=0;
    while(grid[y][x]!=v1){
    x++;
    if(x==N){
    y++;
    x=0;
    assert(y<M);
    }
    }
    if(x==0)
    for(; y>0; y--)
    rot(1, y-1, x);
    else if(x==N-2)
    for(; y>0; y--)
    rot(0, y-1, x-1);
    else
    for(; y>0; y--)
    rotbest(1, y-1, x, 0, y-1, x-1);
    for(; x<N-1; x++)
    rot(1, y, x);
    assert(grid[0][N-1]==v1);
    assert(grid[1][N-1]==v2);
    }else{
    if(grid[1][N-1]!=v1){
    int y=0, x=0;
    while(grid[y][x]!=v1){
    x++;
    if(x==N){
    y++;
    x=0;
    assert(y<M);
    }
    }
    if(y==0){
    if(x==0)
    rot(0, 0, x);
    else if(x==N-2 && grid[1][N-2]==v2)
    rot(1, 0, x-1);
    else
    rotbest(0, 0, x, 1, 0, x-1);
    y++;
    }else{
    if(x==0)
    for(; y>1; y--)
    rot(1, y-1, x);
    else if(x==N-2)
    for(; y>1; y--)
    rot(0, y-1, x-1);
    else
    for(; y>1; y--)
    rotbest(1, y-1, x, 0, y-1, x-1);
    }
    if(M==2)
    for(; x<N-2; x++)
    rot(0, 0, x);
    else
    for(; x<N-2; x++)
    rotbest(0, 0, x, 1, 1, x);
    rot(0, 0, x);
    x++;
    }
    assert(grid[1][N-1]==v1);
    assert(grid[0][N-1]!=v2);
    int y=0, x=0;
    while(grid[y][x]!=v2){
    x++;
    if(x==N){
    y++;
    x=0;
    assert(y<M);
    }
    }
    if(y==0){
    if(x==0)
    rot(0, 0, x);
    else if(x==N-2)
    rot(1, 0, x-1);
    else
    rotbest(0, 0, x, 1, 0, x-1);
    y++;
    }else{
    if(x==0)
    for(; y>1; y--)
    rot(1, y-1, x);
    else if(x==N-2)
    for(; y>1; y--)
    rot(0, y-1, x-1);
    else
    for(; y>1; y--)
    rotbest(1, y-1, x, 0, y-1, x-1);
    }
    if(M==2)
    for(; x<N-2; x++)
    rot(0, 0, x);
    else
    for(; x<N-2; x++)
    rotbest(0, 0, x, 1, 1, x);
    rot(0, 0, x);
    x++;
    }
    assert(grid[0][N-1]==v1);
    assert(grid[1][N-1]==v2);
    }
    for(int i=0; i<M; i++)
    for(int j=0; j<N; j++){
    grid[i][j]=(grid[i][j]/N)*(N-1)+(grid[i][j]%N);
    }
    N--;
    }
    void solve(){
    routelen=0;
    flipped=0;
    if(N==2){
    flip();
    while(N>4){
    solvecolumn();
    }
    flip();
    }else if(M==2){
    while(N>4){
    solvecolumn();
    }
    }else{
    while(M>3 || N>3){
    if(N<M)
    flip();
    solvecolumn();
    }
    }
    if(flipped)
    flip();
    int id=f_id[M][N];
    for(;;){
    unsigned int p=getfinalstate0();
    int mv=finalstate[id][p];
    if(mv==-1)
    break;
    int c=mv>>4;
    int y=(mv>>2)&3;
    int x=mv&3;
    rot(c, y, x);
    }
    }
    #ifndef LOCAL
    int main(){
    init();
    int T=readint();
    while(T--){
    readcase();
    solve();
    printcase();
    }
    return 0;
    }
    #endif 