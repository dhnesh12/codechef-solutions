//https://www.codechef.com/LTIME27/problems/INVERT
# include <bits/stdc++.h>
# define ll long long
using namespace std;

ll mcntinv(deque<ll> &arr, ll low, ll mid, ll high)
{
    ll res=0;
    ll i=low;
    ll j=mid+1;
    while (i<=mid && j<=high)
    {
        if (arr[j]<arr[i])
        {
            res+=(j-i);
            int temp=arr[j];
            arr.erase(arr.begin()+j);
            arr.insert(arr.begin()+i,temp);
            ++mid;
            ++j;
        }
        ++i;
    }
    return res;
}
ll cntinv(deque<ll> &arr, ll low, ll high)
{
    if (low>=high)
        return 0;
    else
    {
        ll mid=(low+high)>>1;
        return cntinv(arr,low,mid)+cntinv(arr,mid+1,high)+mcntinv(arr,low,mid,high);
    }
}

int main()
{
    ll n,q;
    cin>>n>>q;
    deque<ll> arr(n);
    for (ll i=0; i<n; i++)
        cin>>arr[i];
    deque<ll> ch;
    deque<ll> ans;
    for (ll i=0; i<q; i++)
    {
        ll l,r,k;
        cin>>l>>r>>k;
        --l;
        --k;
        --r;
        if (k==ch.size())
        {
            for (ll j=l; j<=r; j++)
                ch.push_back(arr[j]);
        }
        else
        {
            for (ll j=l; j<=r; j++){
                ch.insert(ch.begin()+k+j-l,arr[j]);
            }            
        }
        deque<ll> send=ch;
        ans.push_back(cntinv(send, 0, send.size()-1));
        arr.erase(arr.begin()+l, arr.begin()+r+1);
    }
    for (ll i=0; i<q; i++)
        cout<<ans[i]<<endl;
    return 0;
}