 #include <bits/stdc++.h>
    using namespace std;
     
    vector < pair < int , int > > v[30][30];
     
    int single[30];
     
     
    long long calc(int a , int b){
     
        sort(v[a][b].begin() , v[a][b].end());
     
        vector < pair < int , int > > vec;
     
        for(auto P : v[a][b]){
     
            while(!vec.empty() && vec.back().second <= P.second)
                vec.pop_back();
            vec.push_back(P);
        }
     
        int last = 0;
     
        long long ret = 0;
     
        for(auto P : vec){
     
            ret += 1ll * (P.first - last) * P.second;
     
            last = P.first;
     
        }
     
        return ret;
    }
    int main(){
        int T;
        cin>>T;
        while(T--){
            string str;
            int n;
            cin>>n>>str;
            for(int j = 0 ; j < 30 ; j++){
                single[j] = 0;
                for(int i = 0 ; i < 30 ; i++)
                    v[j][i].clear();
            }
            int last = -1 , c = 0;
            vector < pair < int , int > > letters;
            for(int j = 0 ; j < str.size() ; j++){
                if(str[j] != last){
                    if(j) letters.push_back({last , c});
     
                    last = str[j];
                    c = 1;
                }
                else ++c;
            }
            if(c) letters.push_back({last , c});
     
            for(int j = 0 ; j < letters.size() ; j++){
                int let = letters[j].first - 'a';
                single[let] = max(single[let] , letters[j].second);
            }
            for(int j = 0 ; j + 1 < letters.size() ; j++){
                int a = letters[j].first - 'a' , b = letters[j+1].first - 'a';
                //cout<<a<<' '<<b<<endl;
                v[a][b].push_back({letters[j].second , letters[j+1].second});
            }
     
            long long ans = 0;
     
            for(int j = 0 ; j < 26 ; j++){
                ans += single[j];
                for(int i = 0 ; i < 26 ; i++){
                    ans += calc(j , i);
                }
            }
            cout<<ans<<endl;
        }
    }
