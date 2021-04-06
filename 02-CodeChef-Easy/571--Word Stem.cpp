#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(false); cin.tie(NULL);
#define int long long
#define fo(i,a,n) for(int i=a;i<n;i++)
#define fd(i,a,n) for(int i=a;i>n;i--)
#define maxn 100005
#define mod 1000000007

//ASCII
//'0' - 48
//'9' - 57
//'a' - 97
//'A' - 65

using namespace std;

bool comp(string s1, string s2){
    return (s1.length() <= s2.length());
}

string lcs(string s1, string s2){
    int n1 = s1.length(), n2 = s2.length();
    //dp[i][j] = maximum common chars between 1..i and 1..j substrings of s1 and s2 respectively ending on i and j
    int dp[n1+1][n2+1] = {0};
    int maxlen = INT_MIN, i1, i2;
    memset(dp,0,sizeof(dp));


    fo(i,1,n1+1){
        fo(j,1,n2+1){
            if(s1[i-1]==s2[j-1]){
                dp[i][j] = 1+dp[i-1][j-1];
            }
            if(maxlen < dp[i][j]){
                maxlen = dp[i][j];
                i1 = j-maxlen;
                i2 = j-1;
            }
        }
    }
    string ans_ret = s2.substr(i1, maxlen);
    //cout<<"called"<<endl;
    return ans_ret;
}

int32_t main(){
    fast
    int t;
    cin>>t;
    while(t--){
        //n words
        //longest consecutive substring in all n words
        //ties -> choose lexicographically smaller one

        int n;
        cin>>n;
        vector<string> v(n);
        //string ans;
        fo(i,0,n)
            cin>>v[i];
        if(n==1){
            cout<<v[0]<<endl;
            continue;
        }

        //find all substrings of each word
        //each substring is key in map<key,list> where list is vector of all indices the key is present in
        map<string,vector<int> > m;
        map<string,vector<int> >::iterator it;
        string ans = "";
        fo(i,0,n){
            //all words
            for(int j=0;j<v[i].length();j++){
                //all substrings of word[i]
                for(int k=j;k<v[i].length();k++){
                    string temps = v[i].substr(j,k-j+1);
                    //cout<<temps<<endl;
                    if(find(m[temps].begin(), m[temps].end(), i) == m[temps].end())
                        m[temps].push_back(i);
                }
            }
            //cout<<endl;
        }


        for(it = m.begin(); it!=m.end(); it++){
            string temps = it->first;
            if(m[temps].size() == n){
                if((ans.length() == 0) || (temps.length()>ans.length()))
                    ans = temps;
                else if(ans.length() == temps.length())
                    ans = min(ans, temps);
                //else if(temps.length)
            }
            //if(ans == "grace")
            //    cout<<"YES"<<endl;
        }
        //cout<<m["grace"].size()<<endl;
        cout<<ans<<endl;
    }
    return 0;
}
