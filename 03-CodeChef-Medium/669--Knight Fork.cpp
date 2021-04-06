#include<bits/stdc++.h>

using namespace std;

#define REP(i,a,b) for(int i=a;i<b;i++)

char matrix[1001][1001];
int n,m;

bool isvalid(int x,int y){
  return 0<=x && x<n && y>=0 && y<n;
}
void setmatrix(int x,int y){
  REP(i,0,n){
    if(matrix[i][y]=='0')
      matrix[i][y]='1';
    if(matrix[x][i]=='0')
      matrix[x][i]='1';
  }
  int xtmp,ytmp;
  xtmp=0;
  ytmp=y-x;

  REP(i,0,n){
    if(isvalid(xtmp+i,ytmp+i))
      if(matrix[xtmp+i][ytmp+i]=='0')
        matrix[xtmp+i][ytmp+i]='1';
  }
  xtmp=n-1;
  ytmp=y-(n-1-x);
  REP(i,0,n){
    if(isvalid(xtmp-i,ytmp+i))
      if(matrix[xtmp-i][ytmp+i]=='0')
        matrix[xtmp-i][ytmp+i]='1';
  }
}
int xmov[]={1,2,-2,-1,1,-1,2,-2};
int ymov[]={2,1,-1,-2,-2,2,-1,1};
int attacks(int x,int y){
  int cont=0;
  REP(i,0,8){
    if(isvalid(xmov[i]+x,ymov[i]+y)){
      if(matrix[xmov[i]+x][ymov[i]+y]=='2')
        cont++;
    }
  }
  
  return cont;
}
void print(){
  REP(i,0,n){
    REP(j,0,n){
      cout<<matrix[i][j];
    }
    cout<<endl;
  }
}
int main(){

  int t;
  int x,y;
  cin>>t;
  while(t--){
    cin>>n>>m;
    memset(matrix,'0',sizeof matrix);
    REP(i,0,m){
      cin>>x>>y;
      x--;
      y--;
      matrix[x][y]='2';
      setmatrix(x,y);
    }

    int ans=0;
    REP(i,0,n){
      REP(j,0,n){
        if(matrix[i][j]=='0'){
          if(attacks(i,j)>1)
            ans++;
        }
      }
    }
    cout<<ans<<endl;
    
  }

  return 0;
}