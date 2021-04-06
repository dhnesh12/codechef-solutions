#include<bits/stdc++.h> 
using namespace std; 
#define  FIO    ios_base::sync_with_stdio(false);cin.tie(NULL);
#define  int    long long
#define  pb     push_back
#define  pii    pair<int,int>
#define  f      first
#define  s      second
#define  endl   '\n'
const int mod=1e9+7;
const int Max=1e5+10;
const int Max1=1e6+1;
int n;
int arr[Max],spf[Max1];
vector<pii> temp;


void SPF()
{
    spf[1]=1;
    for(int i=2;i<Max1;i++){
        for(int j=i;j<Max1;j+=i){
            if(spf[j]==0)spf[j]=i;
        }
    }
}
 
 
vector<pii> getPrime(int x)
{
    vector<pii> ans;
    while(x!=1)
    {
        int temp=x,cnt=0;
        while(temp%spf[x]==0){
            temp/=spf[x];cnt++;
        }
        ans.pb({spf[x],cnt});
        x=temp;
    }
    return ans;
}


int32_t main() 
{ 	
    FIO
    SPF();
    
    int t;cin>>t;
    while(t--)
    {
        
        multiset<int> mp[Max1];
        
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>arr[i];
            temp=getPrime(arr[i]);
            for(auto it:temp){
                mp[it.f].insert(it.s);
            }
        }
        
        int ans=1;
        
        for(int i=1;i<Max1;i++)
        {
            if(mp[i].size())
            {
                while(true)
                {
                    auto it=mp[i].end();
                    it--;
                    int last=*it;
                    int start=*mp[i].begin();
                    if(last<=2)break;
                    
                    if(mp[i].size()<n){
                        mp[i].erase(mp[i].find(last));
                        mp[i].insert(last-2);
                        mp[i].insert(1);
                    }
                    else{
                        if(last-2<start)break;
                        mp[i].erase(mp[i].find(last));
                        mp[i].insert(last-2);
                        mp[i].erase(mp[i].find(start));
                        mp[i].insert(start+1);
                    }
                }
                
                if(mp[i].size()==n){
                    int start=*mp[i].begin();
                    ans=ans*pow(i,start);
                }
            }
        }
        
        cout<<ans<<endl;
        
        
        
    }
    
    return 0; 
}

///////////////////////////////////////////////////////////////
////                                                      /////
////                    CAPTAIN1337                       /////
////                                                      /////
///////////////////////////////////////////////////////////////