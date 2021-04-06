#include<bits/stdc++.h>
using namespace std;


int main(){
    long long  t,sum=0,c7=0;
    cin>>t;

    string s;

    while(t--){
        cin>>s;

        sum = 0;
        c7 = 0;
        for(int i=0;i<s.size();i++){
            if(s[i] == '7'){
                c7++;
            }

            else{
                sum+=(s.size()-i)*(c7+1);
                c7 = 0;
            }
        }

        cout<<sum<<endl;

    }

}
