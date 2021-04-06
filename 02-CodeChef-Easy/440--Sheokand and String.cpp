#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0);cin.tie(NULL)
using namespace std;

const int nmax = 3e6+10;
int tsz=0;
int alpha = 96;
int nxt[nmax+1][96];
set<int> WordPasses[nmax+1];
set<int> WordEnds[nmax+1];

int MakeNode(int par){
  if(par== -1) tsz = 0;
  memset(nxt[tsz], -1, sizeof(nxt[tsz]));
  WordPasses[tsz].clear();
  WordEnds[tsz].clear();
  return tsz++;
}

int TrieInsert(string &s, int serial){
  int sz = s.size();
  int cur = 0;
  WordPasses[cur].insert(serial);
  for(int i=0; i<sz; i++){
    int curChar = s[i] - '!';
    if(nxt[cur][curChar] == -1){
      nxt[cur][curChar] = MakeNode(cur);
    }
    cur = nxt[cur][curChar];
    WordPasses[cur].insert(serial);
  }
  WordEnds[cur].insert(serial);
  return cur;
}


pair<int, int> lcpSearch(string &s, int r){
  int lcp = 0, cur = 0;
  int sz = s.size();
  for(int i=0; i<sz; i++){
    if(nxt[cur][s[i]-'!'] != -1){
      if( !WordPasses[ nxt[cur][s[i]-'!'] ].empty() && *(WordPasses[ nxt[cur][s[i]-'!'] ].begin()) <= r ){
        lcp++;
        cur = nxt[cur][s[i]-'!'];
        cout<<s[i];
      }
      else break;
    }
    else break;
  }
  if( !WordEnds[ cur ].empty() && *( WordEnds[ cur ].begin() ) <= r ){
    return make_pair(lcp, cur);
  }
  bool complete = false;
  while(true){
    for(int i=0; i<alpha; i++){
      if(nxt[cur][i] != -1){
        if( !WordPasses[ nxt[cur][i] ].empty() && *(WordPasses[ nxt[cur][i] ].begin()) <= r ){
          cur = nxt[cur][i];
          cout<<char('!'+i);
          if( !WordEnds[ cur ].empty() && *( WordEnds[ cur ].begin() ) <= r ){
            return make_pair(lcp, cur);
          }
          break;
        }
      }
    }
  }
}

int main(){
  fast;
  string s;
  MakeNode(-1);
  int n;
  cin>>n;
  for(int cs=1; cs<=n; cs++){
    cin>>s;
    TrieInsert(s, cs);
  }
  int q, r;
  cin>>q;
  for(int qr=1; qr<=q; qr++){
    cin>>r>>s;
    pair<int, int> ans = lcpSearch(s, r);
    //cout<< ans.first <<' '<<ans.second<<'\n';
    cout<<'\n';
  }
}
