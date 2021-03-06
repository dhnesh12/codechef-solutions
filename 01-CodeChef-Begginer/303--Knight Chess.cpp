#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>
using namespace std;

int checkForMate(long long int x, long long int y, long long int w, long long int z){
         if( (x + 2) == w && (y + 1) == z )
          return 1;
    else if( (x + 2) == w && (y - 1) == z)
          return 1;
    else if( (x - 2) == w && (y + 1) == z)
          return 1;
    else if((x - 2) == w && (y - 1) == z)
          return 1;
    else if((x + 1) == w && (y + 2) == z)
          return 1;
    else if((x - 1) == w && (y + 2) == z)
          return 1;
    else if((x + 1) == w && (y - 2) == z)
          return 1;
    else if((x - 1) == w && (y - 2) == z)
          return 1;
    return 0;
}



int main() {
     int cases;
     cin>>cases;
     while(cases--){
         int n, bit = 0;
         long long int temp , temp2;
         cin>>n;
         vector<int> p(8);
         vector<pair<long long int, long long int>> v(n+1), check(8);
         for(int i = 0; i < n + 1; i++){
             cin>>temp>>temp2;
             v[i] = make_pair(temp , temp2);
         }
        //  check[0] = make_pair(v[n].first     , v[n].second   );
         check[0] = make_pair(v[n].first + 1 , v[n].second   );
         check[1] = make_pair(v[n].first - 1 , v[n].second   );
         check[2] = make_pair(v[n].first ,    v[n].second + 1);
         check[3] = make_pair(v[n].first ,   v[n].second - 1 );
         check[4] = make_pair(v[n].first + 1, v[n].second + 1);
         check[5] = make_pair(v[n].first - 1, v[n].second - 1);
         check[6] = make_pair(v[n].first + 1, v[n].second - 1);
         check[7] = make_pair(v[n].first - 1, v[n].second + 1);
                 
         for(int i = 0; i < n; i++){
            //  temp = v[i].first;
            //  temp2 = v[i].second;
             for(int j = 0; j < 8 && count(p.begin(), p.end(), 0) != 0; j++){
                 if(p[j] == 0){
                    //  cout<<1<<"  ";
                     if(checkForMate(v[i].first, v[i].second, check[j].first, check[j].second))
                       p[j] = 1;
                 }
             }
         }
        //  cout<<p.size();
         int mycount = count(p.begin(), p.end(), 0);
         if(mycount == 0)
             cout<<"YES"<<endl;
         else 
             cout<<"NO"<<endl;
         
     }
	return 0;
}
