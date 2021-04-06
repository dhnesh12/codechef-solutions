#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cassert>
using namespace std;

typedef vector < pair <int, int> > vpii;
typedef vector < vpii > vvpii;
typedef vector < int > vi;
#define D(x) 

int N;
bool F[17][65536]; // (k, i) refers to rectangle of h:2^k, w:2^(N-k) (px,py): (i%(2^k), i/(2^k))

int pow2[20];
int bestrot=0; //rotation of the current best answer
vpii ans, best(65536);
vpii origpoints;

int firstx(int, int);
int firsty(int, int);

//cover rect of size k that contains the point x,y
void coverrect(int x, int y, int k)
{
  int h=pow2[k], w=pow2[N-k];
  F[k][int(x/w)+int(y/h)*(pow2[N]/w)] = true;
}

void origpoint(int x, int y, int excl1=-1, int excl2=-1)
{
  for(int k=0; k<=N; k++){
    if(k>=excl1 and k<=excl2) continue;
    coverrect(x, y, k);
  }
}

// is rectangle of size k that contains the point x,y covered?
bool isrectcovered(int x, int y, int k)
{
  int h=pow2[k], w=pow2[N-k];
  if(firstx(k, int(x/w)+int(y/h)*(pow2[N]/w)) != -1
     and firsty(k, int(x/w)+int(y/h)*(pow2[N]/w)) != -1)
    return false;
  return true;
}

//are the regions we are interested in already covered?
bool iscovered(int x, int y, int excl1=-1, int excl2=-2)
{
  for(int k=0; k<=N; k++){
    if(k>=excl1 and k<=excl2) continue;
    if(!isrectcovered(x, y, k)) return false;
  }
  return true;
}

void newpoint(int x, int y, int excl1=-1, int excl2=-1)
{
  if(!iscovered(x, y, excl1, excl2)){
    origpoint(x, y, excl1, excl2);
    ans.push_back(make_pair(x, y));
  }
}

// returns x-coord of leftmost point in rect (k,i) that isn't covered by vertical rectangles
int firstx(int k, int i)  
{
  //printf("k=%d i=%d\n", k, i);
  if(F[k][i]) return -1;
  if(k==N) return 0;
  
  int w2 = pow2[N-k-1];

  int x1 = i&(pow2[k]-1), y1 = i>>k; // int x1 = i%(pow2[k]), y1 = i/(pow2[k]);
  int x2 = x1<<1, y2 = y1>>1;       // int x2 = x1*2, y2 = y1/2;
  int i2 = (y2<<(k+1)) + x2;        // int i2 = y2*pow2[k+1] + x2;

  int ret;
  
  ret = firstx(k+1, i2);
  if(ret != -1) return ret;
  
  ret = firstx(k+1, i2+1);
  if(ret != -1) return w2+ret;
  
  F[k][i]=true;
  return -1;
}

// returns min y-coord of point in rect (k,i) that isn't covered by horizontal rectangles
int firsty(int k, int i)  
{
  //printf("k=%d i=%d\n", k, i);
  if(F[k][i]) return -1;
  if(k==0) return 0;
  
  int h2 = pow2[k-1];

  int x1 = i&(pow2[k]-1), y1 = i>>k; // int x1 = i%(pow2[k]), y1 = i/(pow2[k]);
  int x2 = x1>>1, y2 = y1<<1;       // int x2 = x1/2, y2 = y1*2;
  int i2 = (y2<<(k-1)) + x2;        // int i2 = y2*pow2[k-1] + x2;
  //printf("i2=%d p2[k-1]=%d k-1=%d\n", i2, pow2[k-1], k-1);
  int ret;
  ret = firsty(k-1, i2);
  //printf("k=%d i=%d ret1=%d\n", k-1, i2, ret);
  if(ret != -1) return ret;
  ret = firsty(k-1, i2+pow2[k-1]);
  //printf("k=%d i=%d ret2=%d\n", k-1, i2+pow2[k-1], ret);
  if(ret != -1) return h2+ret;
  //assert(i<65536);
  F[k][i]=true;
  return -1;
}

bool grid[100][100];

void rotate(vpii &v, int r)
{
  r = (r+100)&3;
  for(int i=0; i<v.size(); i++){
    for(int j=0; j<r; j++){
      swap(v[i].first, v[i].second);
      v[i].first=-v[i].first + pow2[N] -1;
    }
  }
}

void solution1(int p)
{
  for(int i=0; i<origpoints.size(); i++){
    origpoint(origpoints[i].first, origpoints[i].second);
    D(grid[origpoints[i].first][origpoints[i].second]=true;);
  }

  // add fully-pre-determined points
  {
    int w = pow2[N-p], h = pow2[p];
    int I = pow2[N-1]/h, J = pow2[N-1]/w;
    for(int i=0; i<I; i++){
      for(int j=0; j<J; j++){
        newpoint(w*j+i, h*i+j);
      }
    }
  }

  for(int i=0; i<pow2[N]; i++){
    int fx = firstx(0, i);
    if(fx == -1) continue;
    if(i<pow2[N-1]) newpoint(fx, i, 2, N-1);
    else if(fx<pow2[N-1]) newpoint(fx, i, 1, N-2);
    else newpoint(fx, i);
  }
}

void solution2(int p=N/2)
{
  for(int i=0; i<origpoints.size(); i++){
    int x = origpoints[i].first, y = origpoints[i].second;
    //if(x>=pow2[N-1] and y<pow2[N-1]) origpoint(x, y, 2, N-1);
    //else if(x<pow2[N-1] and y>=pow2[N-1]) origpoint(x, y, 1, N-2);
    //else 
    origpoint(x, y);
    D(grid[x][y]=true;);
  }

  
  {
    int w = pow2[N-p], h = pow2[p];
    int I = pow2[N-1]/h, J = pow2[N-1]/w;

    vvpii P;

    for(int i=0; i<I; i++){
      vpii R(J);
      for(int j=0; j<J; j++){
        //newpoint(w*j+i, h*i+j);
        R[j] = make_pair(w*j+i, h*i+j);
      }
      
      int shifty=0;
      for(int j=0; j<J; j++){
        if(shifty<h/2 and j%2==0){
          if(F[0][R[j].second] or F[0][1+R[j].second]){
            shifty+=2;
          }
        }
        R[j].second=R[j].second+shifty;
      }      
      P.push_back(R);
    }

    for(int j=0; j<J; j++){
      int shiftx=0;
      for(int i=0; i<I; i++){
        if(shiftx<w/2 and i%2==0){
          if(F[N][P[i][j].first] or F[N][1+P[i][j].first]){
            shiftx+=2;
          }
        }
        P[i][j].first=P[i][j].first+shiftx;
      }
    }
    
    for(int i=0; i<I; i++){
      for(int j=0; j<J; j++){
        newpoint(P[i][j].first, P[i][j].second);
      }
    }
  }

  vector <int> prefx, prefy;

  for(int i=pow2[N-1]; i<pow2[N]; i++){
    if(F[N][i] and !F[N][i^1]) prefx.push_back(i^1);
    if(F[0][i] and !F[0][i^1]) prefy.push_back(i^1);
  }
  
  int cx=0, cy=0;
  for(int i=0; i<pow2[N-1]; i++){
    int fy = firsty(N, i);
    if(fy == -1) continue;
    if(cy<prefy.size()) newpoint(i, prefy[cy++], 1, N-2);
    else
      newpoint(i, fy, 1, N-2);
  }

  for(int i=0; i<pow2[N]; i++){
    int fx = firstx(0, i);
    if(fx == -1) continue;
    if(i<pow2[N-1]){
      if(cx<prefx.size()) newpoint(prefx[cx++], i, 2, N-1);
      else 
        newpoint(fx, i, 2, N-1);
    }
    else newpoint(fx, i);
  }
}

bool xdone[32768], ydone[32768];

void solution3(int p=N/2)
{
  for(int i=0; i<origpoints.size(); i++){
    int x = origpoints[i].first, y = origpoints[i].second;
    origpoint(x, y);
    if(x<pow2[N-1]) xdone[x]=true;
    if(y<pow2[N-1]) ydone[y]=true;
    D(grid[x][y]=true;);
  }

  {
    int w = pow2[N-p], h = pow2[p];
    int I = pow2[N-1]/h, J = pow2[N-1]/w;

    vvpii P(I, vpii (J, make_pair(-1, -1)));
    
    for(int i=0; i<I; i++){
      int y=h*i;
      for(int j=0; j<J; j++){
        while(y<h*(i+1) and ydone[y]) y++;
        if(y<h*(i+1) and !F[p][j*I*2+i]){
          P[i][j].second = y;
          ydone[y]=true;
        }
      }
    }

    for(int j=0; j<J; j++){
      int x=w*j;
      for(int i=0; i<I; i++){
        while(x<w*(j+1) and xdone[x]) x++;
        if(x<w*(j+1) and !F[p][j*I*2+i]){
          P[i][j].first = x;
          xdone[x]=true;
        }
      }
    }

    for(int i=0; i<I; i++){
      for(int j=0; j<J; j++){
        //printf("%d\n", i*I+j);
        if(P[i][j].first>=0) newpoint(P[i][j].first, P[i][j].second);
      }
    }
  }

  for(int i=0; i<pow2[N]; i++){
    int fx = firstx(0, i);
    if(fx == -1) continue;
    if(i<pow2[N-1]) newpoint(fx, i, 2, N-1);
    else if(fx<pow2[N-1]) newpoint(fx, i, 1, N-2);
    else newpoint(fx, i);
  }

}

void resetall(int r=0)
{
  if(ans.size() < best.size()){
    best = ans;
    bestrot = r;
  }
  ans.clear();
  memset(F, 0, 17*65536);
  memset(xdone, 0, 32768);
  memset(ydone, 0, 32768);
}

int main()
{
  for(int i=0; i<20; i++){
    pow2[i] = 1<<i;
  }

  int M;
  scanf("%d%d", &N, &M);

  int qcount[4]={0};
  for(int i=0; i<M; i++){
    int x, y;
    scanf("%d %d\n", &x, &y);
    origpoints.push_back(make_pair(x, y));
    if(x<pow2[N-1])
      if(y<pow2[N-1]) qcount[0]++;
      else qcount[1]++;
    else
      if(y<pow2[N-1]) qcount[3]++;
      else qcount[2]++;
  }

  int bq=0;
  for(int i=0; i<4; i++){
    if(qcount[i]>qcount[bq])
      bq=i;
  }
  bq=2;
  rotate(origpoints, bq);

  for(int i=0; i<=N; i++){
    solution1(i); resetall();
    //solution2(i); resetall();
    //solution3(i); resetall();
  }

  //solution2(); resetall();
  //solution3(); resetall();

  rotate(best, -bq);
  printf("%d\n", best.size());
  for(int i=0; i<best.size(); i++){
    printf("%d %d\n", best[i].first, best[i].second);
    D( grid[best[i].first][best[i].second]=true; );
  }

  
  double score = max(((1.0*pow2[N]-M)/best.size()) - 1, 0.0);
  //if(score>1.0) assert(best.size()<pow2[N]/4);
  //if(!(1.*bp/N >0.2 and 1.*bp/N<0.4)) score = 0;
  fprintf(stderr, "%lf\n", score);
  
  D(
    for(int y=0; y<pow2[N]; y++){
      for(int x=0; x<pow2[N]; x++){
        if(x%32==0) printf("|");
        else printf(" ");
        if(grid[x][y]) printf("X");
        else printf(".");
      }
      printf("\n");
    }
  );
  

  return 0;
}
