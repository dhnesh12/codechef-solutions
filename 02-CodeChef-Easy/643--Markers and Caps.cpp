#include <bits/stdc++.h>
using namespace std;
//#define int long long

void reverseArray(vector<int>&arr, int start, 
                            int end) 
{ 
    while (start < end) 
    { 
        std::swap(arr[start], arr[end]); 
        start++; 
        end--; 
    } 
} 
  
/* Function to right rotate arr[] 
of size n by d */
void rightRotate(vector<int>&arr, int d, int n) 
{ 
    reverseArray(arr, 0, n-1); 
    reverseArray(arr, 0, d-1); 
    reverseArray(arr, d, n-1); 
} 



signed main()
{
    
    
    int tt;
    cin >> tt;
    
    while(tt--)
    {
       
        int n,i,j;
        cin >> n;
        
        vector<int>a(n),b(n),c(n),d(n);
        vector<pair<int,int>>X;
        map<int,int>mp;
        
        for(int i = 0;i < n;++i)
            {
                cin >> a[i];
                mp[a[i]]++;
                X.push_back({a[i],i});
            }
        sort(X.begin(),X.end());
        
        for(int i = 0;i < n;++i)
        {
            b[i] = X[i].first;
            c[i] = X[i].second;
        }
        
        int maxx = -1;
        
        for(auto it : mp)
        {
            maxx = max(maxx,it.second);
        }
        
        if(maxx > n / 2)
        {
            cout << "No";
        }
        else
        {
            cout << "Yes\n";
            
            rightRotate(b,maxx,n);
           // rightRotate(c,maxx,n);
            
            for(int i = 0;i < n;++i)
            {
                d[c[i]] = b[i];
            }
            
            for(int i = 0;i < n;++i)
            {
               cout << d[i] << " ";
            }
            
        }
        
        cout << '\n';
    }
    
    
    return 0;
}