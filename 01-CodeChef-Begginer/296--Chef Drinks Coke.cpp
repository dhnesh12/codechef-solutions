#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int cases;
	cin>>cases;
	while(cases--){
	    int n , mins, outtemp, range1, range2;
	    cin>>n>>mins>>outtemp>>range1>>range2;
	    vector<pair<int,int>> v(n);
	    for(int i = 0; i < n; i++){
	        cin>>v[i].second>>v[i].first;
	    }
	    int i = 0;
        sort(v.begin(), v.end());
        for(; i < n; i++){
            if(v[i].second > outtemp){
                if(v[i].second - mins <= outtemp){
                    v[i].second = outtemp;
                }
                else v[i].second -= mins;
            }
            else if(v[i].second < outtemp){
                if(v[i].second + mins >= outtemp){
                    v[i].second = outtemp;
                }
                else v[i].second += mins;
            }
            if(v[i].second >= range1 && v[i].second <= range2){
                break;
            }
        }
        if(i == n){
            cout<<-1<<endl;
        }
        else cout<<v[i].first<<endl;
	}
	return 0;
}
