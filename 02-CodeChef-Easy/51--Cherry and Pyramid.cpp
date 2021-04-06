#include <bits/stdc++.h>
using namespace std;

int lps[200004];
vector<int> indices;

// int nandr[200004], r[200004];

void computeLPSArray(string pat, int M); 

void KMPSearch(string pat, string txt) 
{ 
    int M = pat.length();
    int N = txt.length(); 
    
    computeLPSArray(pat, M); 
  
    int i = 0; // index for txt[] 
    int j = 0; // index for pat[] 
    while (i < N) { 
        if (pat[j] == txt[i]) { 
            j++; 
            i++; 
        } 
  
        if (j == M) {
            if(i-j < N/2)
                indices.push_back(i-j);
            // printf("Found pattern at index %d ", i - j); 
            j = lps[j - 1]; 
        } 

        else if (i < N && pat[j] != txt[i]){
            if (j != 0) 
                j = lps[j - 1]; 
            else
                i = i + 1; 
        } 
    } 
} 

void computeLPSArray(string pat, int M) 
{ 
    int len = 0; 
  
    lps[0] = 0; // lps[0] is always 0 
  
    // the loop calculates lps[i] for i = 1 to M-1 
    int i = 1; 
    while (i < M) { 
        if (pat[i] == pat[len]) { 
            len++; 
            lps[i] = len; 
            i++; 
        } 
        else // (pat[i] != pat[len]) 
        { 
            if (len != 0) { 
                len = lps[len - 1]; 
            } 
            else
            { 
                lps[i] = 0; 
                i++; 
            } 
        } 
    } 
}




int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    cin >> s;
     string t;
    cin >> t;
    
    string ss = s+s;
    // cout << ss;
    KMPSearch(t,ss);
    
    int n = s.length();
    int m = t.length();
    
    int qq;
    cin >> qq;
    
    int L, Q, R;
    int ans;
    while(qq--){
        cin >> L;
        Q = L/n;
        R = L%n;
        
        ans = 0;
        
        if(Q >= 2)
            ans += (Q-1)*indices.size();
        
        if(Q >= 1){
            vector<int>::iterator u = upper_bound(indices.begin(), indices.end(), n-m+R);
            ans += (u-indices.begin());
        }
        
        vector<int>::iterator u = upper_bound(indices.begin(), indices.end(), R-m);
        ans += (u-indices.begin());
        cout << ans << "\n";
    }
    
}