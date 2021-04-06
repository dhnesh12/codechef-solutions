#include <cstdio>
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;
typedef int lint;
 
int d,k;
 
int state(int A[]){
  int x = A[1]-A[0]-1;
  int y = A[2]-A[0]-1;
  assert(x < y);
  assert(x >= 0);
  return (y-1)*y/2 + x;
}
 
bool valid(int A[]){
  if(A[1] > A[0] + d) return false;
  if(A[2] > A[1] + d) return false;
  if(A[0] >= A[1]) return false;
  if(A[1] >= A[2]) return false;
  return true;
}
 
bool unmove(int A[], int x){
  A[x]--;
  return false;
}
 
bool move(int A[], int x){
  A[x]++;
  return valid(A) || unmove(A,x);
}
 
const int MOD = 1000000007;
const long long HIGH = 1000000000000000000LL;
 
void multiply(vector<vector<lint> >& A, vector<vector<lint> >& B, vector< vector<lint> >& C){
  assert(A[0].size() == B.size());
  int m = A.size(), r = A[0].size(), n = B[0].size();
 
  static long long temp[130][130];
  for(int i=0;i<m;++i)
    for(int j=0;j<n;++j){
      temp[i][j] = 0;
      for(int k=0;k<r;++k){
        temp[i][j] += (A[i][k] && B[k][j])?(long long int)A[i][k]*B[k][j]:0;
        if(temp[i][j] >= HIGH) temp[i][j] %= MOD;
      }
    }
 
  for(int i=0;i<m;++i)
    for(int j=0;j<n;++j)
      C[i][j] = temp[i][j]%MOD;
}
 
 
main(){
  cin>>d>>k;
  assert(0 <= d && d <= 7);
  assert(0 <= k && k <= 1000000000);
 
  ++d;
  int t = d*(2*d-1);
  vector<vector<lint> > M(t, vector<lint>(t,0));
 
  for(int b=1;b<2*d;++b)
    for(int a=0;a<b;++a){
      int A[]= {-1,a,b};
      int start = state(A);
      for(int i=0;i<3;++i) if(move(A,i)){
        int end = state(A);
        if(end < t) M[end][start]++;
        unmove(A,i);
      }
    }
  
  vector<vector<lint> > P(t, vector<lint>(t,0)), Q = M;
  for(int i=0;i<t;++i) P[i][i] = 1;
  
  while(k){
    if(k&1) multiply(P, Q, P);
    multiply(Q, Q, Q);
    k >>= 1;
  }
 
  lint ret = P[0][0];
  cout<<ret<<endl;
}
 