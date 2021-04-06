#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#define MAX     1000
#define pb       push_back
#define ppb      pop_back
#define f(k,n,p)    for(int i=k; i<=n; i+=p)
#define f(k,n,p)    for(int i=k; i<=n; i+=p)
#define rf(n,k,p)    for(int i=n-1; i>=k; i-=p)
#define rf(n,k,p)    for(int i=n-1; i>=k; i-=p)
#define lli     long long int
#define mod       1000000007
#define ppc     __builtin_popcount
#define ppcll     __builtin_popcountll
#define i2s     to_string
#define gs      getline(cin, s);
#define c_yes   std::cout << "YES" << std::endl;
#define c_no   std::cout << "NO" << std::endl;
typedef   std::vector<int> vi;
typedef   std::vector<lli> vlli;
typedef   std::vector<char> vc;
typedef   std::vector<string> vs;

// class Timer { private: chrono::time_point <chrono::steady_clock> Begin, End; public: Timer () : Begin(), End ()
// { Begin = chrono::steady_clock::now(); } ~Timer () { End = chrono::steady_clock::now();
// cout << "\nDuration: " << ((chrono::duration <double>)(End - Begin)).count() << "s\n"; } } t;

template <class T>
void countSort(vector<T>&arr){
    
    T max = *max_element(arr.begin(), arr.end());
    T min = *min_element(arr.begin(), arr.end());
    int range = max - min + 1;
 
    vector<int> count(range);
    std::vector<T> output(arr.size());
    for (int i = 0; i < arr.size(); i++)
        count[arr[i] - min]++;
 
    for (int i = 1; i < count.size(); i++)
        count[i] += count[i - 1];
 
    for (int i = arr.size() - 1; i >= 0; i--) {
        output[count[arr[i] - min] - 1] = arr[i];
        count[arr[i] - min]--;
    }
 
    for (int i = 0; i < arr.size(); i++)
        arr[i] = output[i];
    
   
}

template <class T>
bool search(vector<T> arr, T n){
    std::vector<T> copy = arr ;
    countSort<T>(copy);
    
    int low = 0, high = arr.size()-1;
    while(low <= high){
        int mid = (low+high)/2;
        
        if (n < copy[mid]){
            high = mid-1;
        }
        else if(n > copy[mid]){
            low = mid + 1;
        }
        else{
            return true;
        }
    }
    
    return false;
    
}

template <class T>
bool isPal(T n){
    
    if(n <= 9) return true;
    
    string s = to_string(n);
    
    
    int i=0, j=s.length()-1;
    while(i<=j){
        if(s[i] != s[j])
            return false;
        i++;j--;
    }
    return true;
}

bool isPrime(int n){
    if(n<=1 || n==4) return false;
    if(n<=3) return true;
    
    for(int i=2; i*i<=n; i++){
        if(n%i==0)return false;
    }
    return true;
}

char survey(int x,int y) {
    std::cout << "S "<<x<<" "<<y << std::endl;
    fflush(stdout);
    char c;
    cin>>c;
    return c;
}

void neutralize(int x, int y){
    std::cout << "N "<<x<<" "<<y<<" " << std::endl;
    fflush(stdout);
}
void solve(){
   
   int n,m,k;
   cin>>n>>m>>k;
   
   map<pair<int, int>, bool> vis;
   
   int dx[8] = {1,-1,1,-1,0,0,1,-1};
   int dy[8] = {1,-1,-1,1,1,-1,0,0};
   f(0,n-1,1){
       for(int j=0; j<n; j++){
           
           if(vis[{i,j}] == true) continue;
           
           char c = survey(i,j);
           
           if(c=='M') neutralize(i,j), m--;
           if(c=='0') {
               int x=i, y=j;
               for(int p=0; p<8 && (x>=0 && x<n && y>=0 && y<n); p++)
                    vis[{x+dx[p], y+dy[p]}] = true;
           }
       }
       
       if(m==0) {
           std::cout << "Done" << std::endl;
           return;
       }
   }
   
   std::cout << "Done" << std::endl;
   
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // int t;
    // cin>>t;
    
    // while(t--)
    solve();
	
	return 0;
}
