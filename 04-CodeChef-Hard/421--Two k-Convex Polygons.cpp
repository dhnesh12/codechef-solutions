#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N =1e3 + 50;
pair<ll,int> A[N];
ll pre[N];
int taken[N];
bool check(int idx , ll s1 , ll s2 , int l1, int l2){
  if(l1 == 0 && l2 == 0){
    if(s1 < 0 && s2 < 0) return true;
    else return false;
  }
  else if(l1 == 0){
    s2 -= A[idx].first;
    --l2;
    taken[idx] = 1;
    if(check(idx+1 , s1 , s2 , l1 , l2)) return true;
    return false;
  }
  else if(l2 == 0){
    s1 -= A[idx].first;
    --l1;
    taken[idx] = 0;
    if(check(idx+1 , s1 , s2, l1 , l2)) return true;
    return false;
  }
  else{
    s1 -= A[idx].first;
    --l1;
    taken[idx] = 0;
    if(check(idx+1 , s1, s2 , l1 , l2)) return true;
    s1 += A[idx].first;
    ++l1;
    s2 -= A[idx].first;
    --l2;
    taken[idx] = 1;
    if(check(idx+1 , s1 , s2 , l1, l2)) return true;
    return false;
  }
}

int main(){
  ll n , k;  cin >> n >> k;
  for(int i = 1;i <= n ; ++i) cin >> A[i].first , A[i].second = i;
  sort(A+1 , A+n+1);
  reverse(A+1 , A+n+1);
  for(int i = 1;i <= n; ++i) pre[i] =pre[i-1] +  A[i].first;
  for(int i = 1;i <= n ; ++i){
    for(int j = i+k;j <= n-k+1 ; ++j){
      if(A[i].first < pre[i+k-1]-pre[i] && A[j].first < pre[j+k-1]-pre[j]){
        cout << "Yes" << endl;
        for(int z = i ; z <= i+k-1 ; ++z)
          cout << A[z].second << ' ';
        for(int z = j ; z <= j+k-1 ; ++z)
          cout << A[z].second << ' ';
        cout << endl;
        return 0;
      }
    }
  }
  for(int i = 1;i <= n-2*k+1 ; ++i){
    for(int j = i+1; j <= min(n-k+1,i+k-1) ; ++j){
      ll lft = A[i].first - pre[j-1] + pre[i];
      ll rht = A[j].first; 
      //cout << i << ' ' << j << ' ' << lft << ' ' << rht << endl;
      if(check(j+1 , lft , rht , k - (j-i) , k-1)){
        cout << "Yes" << endl;
        for(int z = i; z < j ;++z)
          cout << A[z].second << ' ';
        for(int z = j+1; z <= i+2*k-1 ; ++z)
          if(taken[z] == 0) cout << A[z].second << ' ';
        cout << A[j].second << ' ';
        for(int z = j+1;z <= i+2*k-1 ; ++z)
          if(taken[z] == 1) cout << A[z].second << ' ';
        cout << endl;
        return 0;
      }
    }
  }
  cout << "No" << endl;
  return 0;
}
