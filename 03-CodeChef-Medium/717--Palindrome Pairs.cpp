#include <bits/stdc++.h>
using namespace std;

#define rep(i, s, n) for(int i=int(s); i<=int(n); ++i)

#define look6(a,b,c,d,e,f) cerr<<#a<<": "<<a<<" | "<<#b<<": "<<b<<" | "<<#c<<": "<<c<<" | "<<#d<<": "<<d << " | "<<#e<<": "<<e<< " | "<<#f<<": "<<f<< endl;
#define look5(a,b,c,d,e) cerr<<#a<<": "<<a<<" | "<<#b<<": "<<b<<" | "<<#c<<": "<<c<<" | "<<#d<<": "<<d << " | "<<#e<<": "<<e<<endl;
#define look4(a,b,c,d) cerr<<#a<<": "<<a<<" | "<<#b<<": "<<b<<" | "<<#c<<": "<<c<<" | "<<#d<<": "<<d<<endl;
#define look3(a,b,c) cerr <<#a<<": "<<a<<" | "<<#b<<": "<<b<<" | "<<#c<<": "<<c<<endl;
#define look2(a,b) cerr <<#a<<": "<<a<<" | "<<#b<<": "<<b<< endl;
#define look(a) cerr <<#a<<": "<<a<<endl;

long long ans;

unsigned long long mx = 1e6+10, magic = 999983, mod = 1e9+7;

unsigned long long pw[1000050];

struct trie {
    int uptil, below;
    
    trie* child[26];
    
    trie()
	{
		uptil = below = 0;
		
		for (int i=0; i<26; i++)
		    child[i] = nullptr;
	}
    
};

void is_suffix_pal(string w, vector<int>& suffix_pallindrom) {
    
    int n = w.size();
    
    vector<long long> prefix_hash(n);
    vector<long long> suffix_hash(n);
    
    for (int i=0; i<n; i++) {
        prefix_hash[i] = (i == 0 ? 0 : magic*prefix_hash[i-1]) + w[i];
        prefix_hash[i] = prefix_hash[i] % mod;
        
        //look3(w, i, prefix_hash[i]);
        
        //suffix_hash[n-1-i] = (i == 0 ? 0 : magic*suffix_hash[n-i]) + w[n-1-i];
    }
    
    for (int i=n-1; i>=0; i--) {
        suffix_hash[i] = (i == n-1 ? 0 : magic*suffix_hash[i+1]) + w[i];
        suffix_hash[i] = suffix_hash[i] % mod;
        //look3(w, i, suffix_hash[i]);
    }
        
    for (int i=1; i<n; i++) {
        
        long long hash_1 = prefix_hash[n-1] - (prefix_hash[i-1]*pw[n-i]) % mod;
        
        hash_1 = (hash_1 + mod) % mod;
        
        long long hash_2 = suffix_hash[i];
        
        if (hash_1 == hash_2)
            suffix_pallindrom[i] = 1;
        else
            suffix_pallindrom[i] = 0;
            
        //look5(w, i, hash_1, hash_2, suffix_pallindrom[i]);
    }
    
    suffix_pallindrom[n] = 1;
}

void get(trie* curr, string w)
{
    int n = w.length();
    
    reverse(w.begin(), w.end());
   
    vector<int> suffix_pallindrom(n+1, 0);
   
    is_suffix_pal(w, suffix_pallindrom);
   
    for (int i=0; i<n; i++) {
       
       if (curr->child[w[i]-'a'] == nullptr)
        curr->child[w[i]-'a'] = new trie();
        
        curr = curr->child[w[i]-'a'];
        
        ans += suffix_pallindrom[i+1]*curr->uptil;
        
        //look6(w, i, curr->uptil, curr->below, suffix_pallindrom[i+1], ans);
        
        
        if (i == n-1) {
            ans += curr->below;
            break;
        }
        
       
    }
   
}

void insert(trie *curr, string w)
{
   
   int n = w.length();
   
   vector<int> suffix_pallindrom(n+1, 0);
   
   is_suffix_pal(w, suffix_pallindrom);
   
   for (int i=0; i<n; i++) {
       
       if (curr->child[w[i]-'a'] == nullptr)
            curr->child[w[i]-'a'] = new trie();
        
        curr = curr->child[w[i]-'a'];
        
        //look6(w, i, curr->uptil, curr->below, suffix_pallindrom[i+1], "Insert");
        
        if (i == n-1) {
            curr->uptil += 1;
            break;
        }
        
        curr->below += suffix_pallindrom[i+1];
   }
   
   
}


void solve(){
    int n;
    cin >> n;
    
    vector<string>  str_vec(n);
    
    for (int i=0; i<n; i++)
        cin >> str_vec[i];
        
    ans = 0;
        
    auto * root = new trie();
    
    for (int i=0; i<n; i++) {
        get(root, str_vec[i]);
        
        insert(root, str_vec[i]);
    }
    
     auto * new_root = new trie();
        
     for (int i=n-1; i>=0; i--) {
        get(new_root, str_vec[i]);
        
        insert(new_root, str_vec[i]);
    }
    
    cout << ans << "\n";
}

signed main(){
    
    pw[0] = 1;
	rep(i, 1, mx-1)
		pw[i] = (pw[i - 1] * magic)%mod;
		

    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t=1;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}