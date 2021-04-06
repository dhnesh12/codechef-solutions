#include<iostream>
#include<vector>

using namespace std;
typedef long long int ll;

bool isValid(ll n,ll w, ll l, vector<ll> h, vector<ll> r, ll month){
    ll sum = 0;
    for(int i=0;i<n;i++){
        if(h[i] + month*r[i] >l)
        sum += h[i] + month*r[i] ;
        
        if(sum >= w)
        return true;
    }
    return false;
}

ll findMinMonth(ll n,ll w, ll l, vector<ll> h, vector<ll> r){
    ll start = 0;
    ll end;
    if(w%n != 0 ){
        end = w/n + 1 +l;
    }
    else
    end = w/n + l;
    ll mid = start + (end -start)/2;
    ll minMonth = end ;
    while(start <= end){
        if(isValid(n,w,l,h,r,mid)==true){
            minMonth = mid;
            end = mid - 1;
            mid = start + (end -start )/2;
        }
        else{
            start = mid + 1;
            mid = start + (end - start)/2;
        }
    }
    return minMonth;
}

int main(){
    int n;
    ll w,l;
    cin>>n>>w>>l;
    vector<ll> h,r;
    ll x;
    for(int i=0;i<n;i++){
        cin>>x;
        h.push_back(x);
        cin>>x;
        r.push_back(x);
    }
    cout<<findMinMonth(n,w,l,h,r)<<endl;
    return 0;
}