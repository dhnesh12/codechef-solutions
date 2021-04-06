//#include<iostream>
//#include<bits/stdc++.h>
//#define ll long long
//#define pb push_back
//#define inf 1000000007
//#define all(x) (x).begin(), (x).end()
//using namespace std;
//
//#define debug(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); deb(_it, args); }
//void deb(istream_iterator<string> it) {cout<<endl;}
//template<typename T, typename... Args>
//void deb(istream_iterator<string> it, T a, Args... args) {
//    cerr << *it << " = " << a << ",   ";
//    deb(++it, args...);
//}
//
//const int bitn = 43;
//
//bool adj[bitn][bitn];
//
//map<int, int> factorMap;
//set<pair<int, int>> factorSet;
//
//void factorize(ll num){
//    for(int i=2; i*i<=num; i++){
//        if(num%i==0){
//            while(num%i==0){
//                factorSet.erase({i, factorMap[i]});
//                factorMap[i]++;
//                factorSet.insert({i, factorMap[i]});
//                num/=i;
//                if(factorMap[i]>=3) return;
//            }
//        }
//    }
//    if(num>1){
//        factorSet.erase({num, factorMap[num]});
//        factorMap[num]++;
//        factorSet.insert({num, factorMap[num]});
//    }
//    return;
//}
//
//bool adjacent(ll x, ll y){
//
//    factorMap.clear();
//    factorSet.clear();
//
//    factorize(x);
//
//    factorize(y);
//
//    bool ans = true;
//    for(auto a : factorSet){
//
//        if(a.second>=3){
//
//            ans = false;
//            break;
//        }
//    }
//
//    return ans;
//}
//
////unordered_map<int, int> factorsMap;
////set<pair<int, int> > factorsSet;
////
////void factorize(int x) {
////	for (int i = 2; i * i <= x; i++)
////		while (x % i == 0) {
////			factorsSet.erase({i, factorsMap[i]});
////			factorsMap[i]++;
////			factorsSet.insert({i, factorsMap[i]});
////			if (factorsMap[i] >= 3) //for optimization
////				return;
////			x /= i;
////		}
////	if (x > 1) {
////		factorsSet.erase({x, factorsMap[x]});
////		factorsMap[x]++;
////		factorsSet.insert({x, factorsMap[x]});
////	}
////}
////
////bool adjacent(int x, int y) {
////	factorsMap.clear();
////	factorsSet.clear();
////	factorize(x);
////	factorize(y);
////	for (auto i: factorsSet)
////		if (i.second >= 3)
////			return false;
////	return true;
////}
//
//
//int main()
//{
//    ios::sync_with_stdio(false); cin.tie(0);
//    int t;
//    cin>>t;
//    while(t--){
//        int n;
//        cin>>n;
//        int half = n/2;
//        ll a[n+100];
//        bool isClique[(1<<(n-half))+100];
//        ll dp[(1<<(n-half))+100];
//        ll lastPartNeighbour[n+100];
//
//        memset(dp, 0, sizeof dp);
//        memset(adj, 0, sizeof adj);
//        memset(isClique, false, sizeof isClique);
//        memset(lastPartNeighbour, 0, sizeof lastPartNeighbour);
//
//        for(int i=0; i<n; i++){
//            cin>>a[i];
//        }
//
//        for(int i=0; i<n; i++){
////            if(i<half){
////               lastPartNeighbour[i] |= (1<<(i));
//////               debug(lastPartNeighbour[i] )
////            }
//            for(int j=i+1; j<n; j++){
//                if(adjacent(a[i], a[j])){
//                    if(i<half){
//                        lastPartNeighbour[j] |= (1<<(i));
//                    }
//                    if(j<half){
//                        lastPartNeighbour[i] |= (1<<(j));
//                    }
//
//                    adj[j][i] = adj[i][j] = true;
//                }
//            }
//        }
//
//
//        isClique[0] = true;
//
////        for(int i=0; i<n-half; i++){
////            for(int mask=1; mask< 1<<(n-half); mask++){
////                if((mask &(1<<i))){
//////                        debug(i, mask, half+i,lastPartNeighbour[half+i])
////                    if(((mask & lastPartNeighbour[half+i]) == mask))
////                        isClique[mask] &= isClique[mask^(1<<i)];
////                    else isClique[mask] = false;
////                }
////            }
////        }
//
//        for (int mask = 1; mask < (1 <<(half)); mask++) {
//			int v = __builtin_ctz(mask);
//			int mask2 = (mask ^ (1 << v));
//			if (!isClique[mask2]) {
//				isClique[mask] = false;
//				continue;
//			}
//			isClique[mask] = true;
//			for (int i = 0; i < half; i++) {
//				if ((mask2 & (1 << i)) && !adj[i][v]) {
//					isClique[mask] = false;
//					break;
//				}
//			}
//		}
//
//
//        dp[0] = 1;
//        for(int mask=1; mask<(1<<(n-half)); mask++){
//            int v = __builtin_ctz(mask);
//            int mask2 = mask^(1<<v);
//            dp[mask] = dp[mask2];
//
//            int mask3 = 0;
//            for(int i=0; i<n-half; i++){
//                if((mask&(1<<i)) && adj[half+i][half+v]){
//                    mask3|=(1<<i);
//                }
////                debug(i, mask3)
//            }
//
//            dp[mask]+=dp[mask3];
////            debug(mask, dp[mask], mask2, dp[mask2], mask3, dp[mask3]);
//        }
//
//
//        ll ans = 0;
//
//        for(int mask = 0; mask<(1<<(half)); mask++){
//            if(isClique[mask]==false){
////                debug("shit",mask)
//                continue;
//            }
//            int mask2 = 0;
//            for(int i=half; i<n; i++){
//                if((lastPartNeighbour[i]&mask)==mask) mask2|=(1<<(i-half));
//            }
////            debug(mask, mask2, dp[mask2])
//            ans+=dp[mask2];
//        }
//
//        cout<<ans<<endl;
//    }
//
//    return 0;
//}
//
///*
//
//22
//2
//1 2
//
//3
//5
//5 1 4 2 3
//
//33
//5
//2 4 5 1 3
//
//33
//5
//2 3 5 1 3
//*/


#include<iostream>
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define inf 1000000007
#define all(x) (x).begin(), (x).end()
using namespace std;

#define debug(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); deb(_it, args); }
void deb(istream_iterator<string> it) {cout<<endl;}
template<typename T, typename... Args>
void deb(istream_iterator<string> it, T a, Args... args) {
    cerr << *it << " = " << a << ",   ";
    deb(++it, args...);
}

const int bitn = 43;

bool adj[bitn][bitn];

map<int, int> factorMap;
set<pair<int, int>> factorSet;

void factorize(ll num){
    for(int i=2; i*i<=num; i++){
        if(num%i==0){
            while(num%i==0){
                factorMap[i]++;
                num/=i;
                if(factorMap[i]>=3) return;
            }
        }
    }
    if(num>1){
        factorMap[num]++;
    }
    return;
}

bool adjacent(ll x, ll y){

    factorMap.clear();

    factorize(x);

    factorize(y);

    bool ans = true;
    for(auto a : factorMap){

        if(a.second>=3){

            ans = false;
            break;
        }
    }

    return ans;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        int half = n/2;
        ll a[n+100];
        bool isClique[(1<<(n-half))+100];
        ll dp[(1<<(n-half))+100];
        ll lastPartNeighbour[n+100];

        memset(dp, 0, sizeof dp);
        memset(adj, 0, sizeof adj);
        memset(isClique, false, sizeof isClique);
        memset(lastPartNeighbour, 0, sizeof lastPartNeighbour);

        for(int i=0; i<n; i++){
            cin>>a[i];
        }

        for(int i=0; i<n; i++){
//            if(i<half){
//               lastPartNeighbour[i] |= (1<<(i));
////               debug(lastPartNeighbour[i] )
//            }
            for(int j=i+1; j<n; j++){
                if(adjacent(a[i], a[j])){
                    if(i<half){
                        lastPartNeighbour[j] |= (1<<(i));
                    }
                    if(j<half){
                        lastPartNeighbour[i] |= (1<<(j));
                    }

                    adj[j][i] = adj[i][j] = true;
                }
            }
        }


        isClique[0] = true;

//        for(int i=0; i<n-half; i++){
//            for(int mask=1; mask< 1<<(n-half); mask++){
//                if((mask &(1<<i))){
////                        debug(i, mask, half+i,lastPartNeighbour[half+i])
//                    if(((mask & lastPartNeighbour[half+i]) == mask))
//                        isClique[mask] &= isClique[mask^(1<<i)];
//                    else isClique[mask] = false;
//                }
//            }
//        }

        for (int mask = 1; mask < (1 <<(half)); mask++) {
			int v = __builtin_ctz(mask);
			int mask2 = (mask ^ (1 << v));
			if (!isClique[mask2]) {
				isClique[mask] = false;
				continue;
			}
			isClique[mask] = true;
			for (int i = 0; i < half; i++) {
				if ((mask2 & (1 << i)) && !adj[i][v]) {
					isClique[mask] = false;
					break;
				}
			}
		}


        dp[0] = 1;
        for(int mask=1; mask<(1<<(n-half)); mask++){
            int v = __builtin_ctz(mask);
            int mask2 = mask^(1<<v);
            dp[mask] = dp[mask2];

            int mask3 = 0;
            for(int i=0; i<n-half; i++){
                if((mask&(1<<i)) && adj[half+i][half+v]){
                    mask3|=(1<<i);
                }
//                debug(i, mask3)
            }

            dp[mask]+=dp[mask3];
//            debug(mask, dp[mask], mask2, dp[mask2], mask3, dp[mask3]);
        }


        ll ans = 0;

        for(int mask = 0; mask<(1<<(half)); mask++){
            if(isClique[mask]==false){
//                debug("shit",mask)
                continue;
            }
            int mask2 = 0;
            for(int i=half; i<n; i++){
                if((lastPartNeighbour[i]&mask)==mask) mask2|=(1<<(i-half));
            }
//            debug(mask, mask2, dp[mask2])
            ans+=dp[mask2];
        }

        cout<<ans<<endl;
    }

    return 0;
}

/*

22
2
1 2

3
5
5 1 4 2 3

33
5
2 4 5 1 3

33
5
2 3 5 1 3
*/

