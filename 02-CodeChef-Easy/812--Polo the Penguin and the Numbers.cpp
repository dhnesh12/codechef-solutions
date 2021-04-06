#include<bits/stdc++.h>
using namespace std;
#define ld long double
#define ll long long
#define mod 1000000007
#define ul unordered_map <ll,ll>
#define uc unordered_map <char,ll>
#define us unordered_map <string,ll>
#define vl vector <ll>
#define vc vector <char>
#define vs vector <string>
#define srt(arr) sort(arr.begin(),arr.end())
#define pb push_back

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll t;
    cin>>t;
    while(t--){
        ll l,r;
        cin>>l>>r;
        ll sum=0;
        ll temp=10;
        bool b=true;
        while(b){
            if(l>=temp){
                temp=temp*10;
            }else if(l<temp && r>=temp){
                ll temp_sum=((temp-1)*(temp))/2;
                sum+=((temp_sum-((l-1)*(l))/2)*(to_string(temp).length()-1))%mod;
                l=temp;
            }else if(l<temp && r<temp){
                sum+=((((r*(r+1))-((l-1)*l))/2) * to_string(r).length())%mod;
                break;
            }
        }
        cout<<sum%mod<<endl;
    }
}
