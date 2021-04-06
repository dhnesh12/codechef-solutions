#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace std;
using namespace __gnu_pbds;
 
#define F first
#define S second
#define mp make_pair
#define pb push_back
#define pf push_front
#define eb emplace_back
#define f(i,x,n) for(ll i=x;i<n;i++)
#define all(c) c.begin(),c.end()
#define rall(c) c.rbegin(),c.rend()
#define int ll

template < typename T > using indexed_set = tree < T, null_type, less < T >, rb_tree_tag, tree_order_statistics_node_update >;
template < typename T > using MinPriorityQueue = priority_queue < T, vector < T >, greater < T > >;

using ll = long long;
using db = double;
using pii = pair < int, int >;
using pll = pair < ll, ll >;
 
const double PI = acos(-1);
const ll LINF = LLONG_MAX;
const int MOD = 1e9+7, INF = INT_MAX, N = 5e5 + 10;
 
int seen[N];

int GetCeilIndex(vector<int>& arr, vector<int>& T, int l, int r,int key) 
{ 
   while (r - l > 1) { 
   int m = l + (r - l) / 2; 
   if (arr[T[m]] >= key) 
      r = m; 
   else
      l = m; 
   } 

   return r; 
} 
  
vector<int> LongestIncreasingSubsequence(vector<int> &arr, int n) 
{
   vector<int> tailIndices(n, 0);  
   vector<int> prevIndices(n, -1); 

   int len = 1; 
   for (int i = 1; i < n; i++) { 
     if (arr[i] < arr[tailIndices[0]]) { 
         tailIndices[0] = i; 
     } 
     else if (arr[i] > arr[tailIndices[len - 1]]) { 
         prevIndices[i] = tailIndices[len - 1]; 
         tailIndices[len++] = i; 
     } 
     else { 
      
         int pos = GetCeilIndex(arr, tailIndices, -1,len - 1, arr[i]); 
         prevIndices[i] = tailIndices[pos - 1]; 
         tailIndices[pos] = i; 
     } 
   } 
   vector<int> res;
   for (int i = tailIndices[len - 1]; i >= 0; i = prevIndices[i]) 
     res.pb(arr[i]);
   reverse(all(res)); 
   return res;
}

void print(vector<int> &a){
   for(auto &e : a){
      cout << e << ' ';
   }
   cout << '\n';
}

int32_t main(){
   ios::sync_with_stdio(false);
   cin.tie(NULL);
   int n,k;
   cin >> n >> k;
   vector<int> a(n);
   vector<int> tmp,tmp1;
   vector<vector<int>> tmm,tmm1;
   vector<int> tmp3,tmp2,d,e;
   int kk = (n+k-1)/k;

   vector<int> b1,c1;

   vector<int> ar(n+1,0),pos(n+1);

   f(i,0,n){
      cin >> a[i];
      ar[i+1] = a[i];
      if(i<k){
         tmp.pb(a[i]);
      }
      if(i>=n-k){
         tmp1.pb(a[i]);
      }
      if(i%kk == 0){
         tmm.pb(tmp2);
         tmp2.clear();
      }
      tmp2.pb(a[i]);
      if(i==n-1){
         tmm.pb(tmp2);
      }
   }

   b1 = a;
   c1 = a;

   f(i,1,n+1){
      pos[ar[i]] = i;
   }

   sort(b1.begin(),b1.begin()+k-1);
   sort(c1.begin()+n-k+1,c1.end());

   vector<int> aa = a;
   reverse(all(aa));

   f(i,0,n){
      if(i%kk==0){
         tmm1.pb(tmp3);
         tmp3.clear();
      }
      tmp3.pb(aa[i]);
      if(i==n-1){
         tmm1.pb(tmp3);
      }
   }

   sort(all(tmm));
   sort(all(tmm1));
   f(i,0,tmm.size()){
      for(auto &e : tmm[i]){
         d.pb(e);
      }
      reverse(all(tmm1[i]));
      for(auto &ee : tmm1[i]){
         e.pb(ee);
      }
   }
   vector<int> b;
   vector<int> c;
   sort(all(tmp));
   sort(all(tmp1));
   f(i,0,k){
      if(tmp[i] == a[k-1]){
         b.pb(tmp[i]);
         f(j,k,n){
            b.pb(a[j]);
         }
      }else{
         b.pb(tmp[i]);
      }
      if(tmp1[i] == a[n-k]){
         f(j,0,n-k){
            c.pb(a[j]);
         }         
         c.pb(tmp1[i]);
      }else{
         c.pb(tmp1[i]);
      }
   }

   if(k==n){
      sort(all(a));
      f(i,0,n){
         cout << a[i] << ' ';
      }
      return 0;
   }

   set<int> ss;
   ss.insert(n);
   ss.insert(0);
   vector<int> f;
   vector<int> lis = LongestIncreasingSubsequence(a,n);
   vector<int> lis1 = LongestIncreasingSubsequence(b,n);
   vector<int> lis2 = LongestIncreasingSubsequence(c,n);
   vector<int> lis3 = LongestIncreasingSubsequence(d,n);
   vector<int> lis4 = LongestIncreasingSubsequence(e,n);
   vector<int> lis5 = LongestIncreasingSubsequence(b1,n);
   vector<int> lis6 = LongestIncreasingSubsequence(c1,n);
   
   for(int i=n;i>0;i--){
     if(ss.size() == k+1) break;
     if(ar[pos[i]+1]!=i+1){
      ss.insert(pos[i]);
     }
     if(ar[pos[i]-1]!=i-1){
        if(ss.size()!=k+1)
          ss.insert(pos[i]-1);
      }
   }

   f(i,1,n+1){
      if(!seen[i]){
         auto k = ss.upper_bound(pos[i]-1);
         int u = *k;
         k--;
         int l = *k+1;
         f(j,l,u+1){
            seen[ar[j]] = 1;
            f.pb(ar[j]);
         }
      }
   }

   vector<int> lis7 = LongestIncreasingSubsequence(f,n);
   int mxl = max({lis.size(),lis1.size(),lis2.size(),lis3.size(),lis4.size(),lis5.size(),lis6.size(),lis7.size()});
   // print(f);
   // return 0;
   if(mxl == (int)lis7.size()){
      print(f);
      return 0;
   }
   if(mxl == (int)lis5.size()){
      print(b1);
      return 0;
   }
   if(mxl == (int)lis6.size()){
      print(c1);
      return 0;
   }
   if(mxl == (int)lis4.size()){
      print(e);
      return 0;
   }
   if(mxl == (int)lis1.size()){
      print(b);
      return 0;
   }
   if(mxl == (int)lis2.size()){
      print(c);
      return 0;
   }
   if(mxl == (int)lis3.size()){
      print(d);
      return 0;
   }
   if(lis1.size() > lis.size() and lis1.size() > lis2.size()){
      f(i,0,n){
         cout << b[i] << ' ';
      }
      return 0;
   }
   if(lis2.size() > lis.size() and lis2.size() > lis1.size()){
      f(i,0,n){
         cout << c[i] << ' ';
      }
      return 0;
   }
   if(lis2.size() > lis.size()){
      f(i,0,n){
         cout << b[i] << ' ';
      }
      return 0;  
   }
   if(lis1.size() > lis.size()){
      f(i,0,n){
         cout << c[i] << ' ';
      }
      return 0;  
   }
   if(k==3){
      if(!binary_search(all(lis),a[0])){
         auto kk = lower_bound(all(lis),a[0]);
         if(kk==lis.end()){
            f(i,1,n){
               cout << a[i] << ' ';
            }
            cout << a[0] << '\n';
            return 0;
         }
         f(i,1,n){
            if(a[i]==*kk){
               cout << a[0] << ' ' << a[i] << ' ';
            }else{
               cout << a[i] << ' ';
            }
         }
         return 0;
      }
      if(!binary_search(all(lis),a[n-1])){
         auto kk = lower_bound(all(lis),a[n-1]);
         f(i,0,n-1){
            if(a[i]==*kk){
               cout << a[n-1] << ' ' << a[i] << ' ';
            }else{
               cout << a[i] << ' ';
            }
         }
         return 0;
      }
      if(!binary_search(all(lis),*max_element(all(a)))){
         f(i,0,n){
            if(a[i] == *max_element(all(a))){
               continue;
            }
            cout << a[i] << ' ';
         }
         cout << *max_element(all(a)) << '\n';
         return 0;
      }
      if(!binary_search(all(lis),*min_element(all(a)))){
         cout << *min_element(all(a)) << ' ';
         f(i,0,n){
            if(a[i] == *min_element(all(a))){
               continue;
            }
            cout << a[i] << ' ';
         }
         return 0;
      }
   }else{
      f(i,0,n){
         if(!binary_search(all(lis),a[i])){
            auto kk = lower_bound(all(lis),a[i]);
            if(kk==lis.end()){
               f(j,0,n){
                  if(a[i]==a[j]) continue;
                  cout << a[j] << ' ';
               }
               cout << a[i] << ' ';
            }else{
               f(j,0,n){
                  if(i==j) continue;
                  if(a[j]==*kk){
                     cout << a[i] << ' ' << a[j] << ' ';
                  }else{
                     cout << a[j] << ' ';
                  }
               }
            }
            return 0;
         }
      }
   }
   return 0;
}