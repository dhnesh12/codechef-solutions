#include <bits/stdc++.h>
using namespace std;

int n; 
string s;

void solve(){
    scanf("%d",&n);
    cin>>s;
    
    int l,r,ans=0;
    bool lflag=false, rflag=false;
    for(l=0,r=n-1;l<r;++l,--r){
        if(s[l]==s[r]){
            lflag=rflag=false;
            continue;
        }
        if(l+1==r){
            printf("NO");
            return;
        }
        if(!lflag && s[l+1]==s[r]){
            swap(s[l],s[l+1]);
            lflag=true;
            rflag=false;
            ans++;
        }
        else if(!rflag && s[l]==s[r-1]){
            swap(s[r],s[r-1]);
            lflag=false;
            rflag=true;
            ans++;
        }
        else{
            printf("NO");
            return;
        }
    }
    printf("YES\n%d",ans);
}

int main() {
	int t; scanf("%d",&t);
	while(t--){
	    solve();
	    printf("\n");
	}
	return 0;
}
