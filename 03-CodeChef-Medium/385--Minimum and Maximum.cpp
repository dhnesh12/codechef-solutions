#include <bits/stdc++.h>

#define int long long
#define fi first
#define se second
using namespace std;
vector<int> can[1010];
int n;
int ask(int x, int y){
    cout<<1<<" "<<x<<" "<<y<<endl;
    int z;
    cin>>z;
    return z;
}
int build(int l, int r, vector < int > A, bool for_min)
{
        if(l == r){
                return A[l];
        }
        int m = (l + r) / 2;
        int x = build(l, m, A, for_min), y = build(m + 1, r, A, for_min);

        int need = ask(x, y), op = x ^ y ^ need;
        if(for_min == false){
                swap(need, op);
        }

        can[need].push_back(op);
        return need;
}
void solve(){
    cin >> n;
	    for(int i = 1; i <= n; i++){
	            can[i].clear();
	    }

	    vector < int > A, B;
	    for(int i = 1; i + 1 <= n; i += 2){
	            int j = ask(i, i + 1), h = i ^ (i + 1) ^ j;
	            A.push_back(j);
	            B.push_back(h);

	            can[j].push_back(h);
	            can[h].push_back(j);
	    }
	    if(n & 1){
	            A.push_back(n);
	            B.push_back(n);
	    }

	    int min_1 = build(0, (int)A.size() - 1, A, true);
	    int max_1 = build(0, (int)B.size() - 1, B, false);
	    int min_2 = -1, max_2 = -1;

	    for(int x: can[min_1]){
	            if(min_2 == -1 || ask(x, min_2) == x){
	                    min_2 = x;
	            }
	    }
	    for(int x: can[max_1]){
	            if(max_2 == -1 || ask(x, max_2) == max_2){
	                    max_2 = x;
	            }
	    }

	    cout << 2 << " " << min_1 << " " << min_2 << " " << max_2 << " " << max_1 << endl;
}

signed main(){
    int t=1;
    cin>>t;
    while(t--){
        solve();
    }
}