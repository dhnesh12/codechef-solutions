#include<bits/stdc++.h>
using namespace std;
signed main(){int grundy[202]; grundy[0] = 0; grundy[1] = 1; grundy[2] = 2;
    for (int i = 3;i<=200;i++){int arr[3];arr[0]=-1;arr[1]=-1;arr[2]=-1;arr[grundy[i-1]]=1;arr[grundy[i-2]]=1;
        for (int j = 0; j < 3; j++){if (arr[j] == -1){grundy[i] = j;break;}}} int t; cin >> t;
    for (int i = 0; i < t; i++){string s; cin >> s; int g = 0; vector<int> posi;
        for (int j = 0; j < s.size(); j++){if (s[j] == 'P'){posi.push_back(j);}}
        for (int j = posi.size()-1; j >= 0; j -= 2){if (j > 0){g ^= grundy[posi[j]-posi[j-1]-1];}
            else{g ^= grundy[posi[j]-0];}} if (g > 0){cout << "Yes" << endl;} else{cout <<"No" << endl;}}}