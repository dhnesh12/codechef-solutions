#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int searchHash(int pos, vector<string> vec){
    int ans = -1;
    for(int i=pos;i<vec.size();i++){
        if(vec[i][vec[i].length()-1] == '#')
           { ans = i; break;}
    }
    return ans;
}
void solve(){
    
    string str = "a";
    bool hasEnded = 0;
    vector<string> vec;
    
    while(str[str.length()-1] != '~'){
        cin>>str;
        vec.push_back(str);
    }
    // for(string item: vec){
    //     cout<<item<<" ";
    // }
    // cout<<"\n";
    int start = 0;
    bool flag = 0;
    string ans = "";
    
            
    for(int i=0;i<vec.size();i++){
        
            if(vec[i][0] == '0')
            {
                string temp = vec[i];
                // cout<<"string is "<<temp<<"\n";
                // cout<<"here\n";
                if(temp.length() == 1)
                    flag = 1;
                else if(temp.length() == 2)
                    flag = 0;
                else if(temp.length() > 2)
                    for(int i=0;i<temp.length()-2;i++){
                        // cout<<"here\n";
                        if(flag)
                            ans += '1';
                        else
                            ans += '0';
                    }
                temp = "";
            }
            else if(vec[i][0] == '#')
            {
                int final = 0;
                for(int i=ans.length()-1, j=0;i>=0;i--,j++){
                    if(ans[i] == '1'){
                        final += pow(2,j) * 1;
                    }
                }
                cout<<final<<"\n";
                ans = "";
            }
            else if(vec[i][0] == '~')
                break;
           
               
    }
     
}


int main() {
	solve();
	return 0;
}
