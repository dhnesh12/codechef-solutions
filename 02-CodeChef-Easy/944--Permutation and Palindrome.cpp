#include<bits/stdc++.h>
using namespace std;
char getChar(int i){
    return (char)(i+97);
}

void printPalindromicString(string s){
    map<char,vector<int>>indexesMap;
    for(int i = 0;i <s.length();i++){
        indexesMap[s[i]].push_back(i);
    }

    int odd_freq_count = 0;
    for(int i = 0;i < 26;i++){
        if((indexesMap[getChar(i)].size() % 2) !=0){
            odd_freq_count++;
        }
    }
    if(odd_freq_count >= 2){
        cout<<"-1";
        return;
    }

     int ans[s.length()];
     int start = 0;
     int end = s.length() - 1;
     for(int i = 0;i < 26;i++){
        char current_char = getChar(i);
        for(int j =0 ;j < indexesMap[current_char].size();j+=2){
            
            if((indexesMap[current_char].size() - j) == 1){
                ans[s.length()/2] = indexesMap[current_char][j];
                continue;
            }
            ans[start] = indexesMap[current_char][j];
            ans[end] = indexesMap[current_char][j+1];
            start++;
            end--;
        }
     }
     for(int i = 0;i < s.length();i++){
        cout << ans[i] + 1 <<" ";
     }
     return;
}

int main(){
// #ifndef ONLINE_JUDGE
//     freopen("input.txt","r",stdin);
//     freopen("output.txt","w",stdout);
// #endif

     int t;
     cin>>t;
     while(t--){
        string s;
        cin>>s;
        printPalindromicString(s);
        cout<<endl;
     }
    return 0;
}