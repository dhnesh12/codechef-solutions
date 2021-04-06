#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
int main(){
    int N, c;
    cin>>N>>c;
    int cost = 1000;
    int l = 1, r = N;
    int mid;
    while( l < r ){
        mid = (9*l+r)/10;
        cout<<"1 "<<mid<<'\n';
        --cost;
        fflush(stdout);
        int res; cin>>res;
        if( res == 1 ){
            cout<<"2\n";
            fflush(stdout);
            cost -= c;
            r = mid;
        }
        else l = mid+1;
    }
    cout<<"3 "<<l<<'\n';
    return 0;
}
/*
 -find the letter which occurs the most
 -the count of that letter would be the answer

 -find the least distance between two breeds
 -and remodel the problem as least distance between b1 & bk
 -
*/