#include<bits/stdc++.h>  
//-- code_by_usernameharsh -- 
using namespace std;
#define ll long long int
#define co cout<<
#define test() ll T; cin>>T; for(ll tc=0;tc<T;tc++)

#define f0i(n) for(ll i=0;i<n;i++)
#define f0j(n) for(ll j=0;j<n;j++)
#define f0k(n) for(ll k=0;k<n;k++)

#define f1i(n) for(ll i=1;i<=n;i++)
#define f1j(n) for(ll j=1;j<=n;j++)
#define f1k(n) for(ll k=1;k<=n;k++)



class graph{
    public : 
};

int main(){
    /*ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);*/

    /*#ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif*/

    ll m[5][5] = {{-1,0,5,5,0},{1,-1,1,6,6},{7,2,-1,2,7},{8,8,3,-1,3},{4,9,9,4,-1}};
    ll n[5][5] = {{-1,1,7,8,4},{0,-1,2,8,9},{5,1,-1,3,9},{5,6,2,-1,4},{0,6,7,3,-1}}; 

    char p[] = {0, 1, 2, 3, 4};
    char q[] = {5, 6, 7, 8, 9};

    ll  i, l;
    string s; 
    test(){
        cin>>s;
        
        bool flag = true;
        i = 1;
        l = 1;
        while(i < s.length() ){
          if(s[i] == s[i-1]){
              i++;
              l++;
          }else{
              break;
          }
        }

        string prefix="";
        if(i == s.length()){
            ll a = (ll)s[0]-65;
            ll k = p[a];
            while(l--){
                prefix += (char)(k+48);
                k = (k == p[a])? q[a] : p[a];
            }
            co prefix<<"\n";
        }else{
            ll  a = (ll)s[i-1]-65, b =  (ll)s[i]-65;
            ll k = m[a][b]  ;
            
            while(l--){
                prefix += (char)(k+48) ;
                k = ( k == p[a] )  ? q[a]  : p[a] ;
            }
            //co prefix<<" ";
            
            reverse(prefix.begin(), prefix.end());

            string ans="";
            ans += prefix; 

            k = n[a][b];
            ans += (char)(k + 48);

            i++;
            while(i <s.length()){
                a = (int)s[i-1]-65,b = (int)s[i]-65;

                if( a != b ){
                    if( m[a][b] != k ){
                        flag = false;
                        break; 
                    }else{
                        k = n[a][b];
                        ans += (char)(k+48);
                    }
                }else{
                    k = ( k == p[a]) ? q[a] : p[a];
                    ans +=  (char)(k+48);
                }
                i++;
            }
            if(flag)
                co ans<<"\n";
            else
                co "-1\n";
        }
    }
}



/*
testCase 1  :-
5
AAA 
B
CCCC 
DDDDD 
EEE  
 :-
050
1
2727
38383
494



*/