#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>
#include <cmath>
using namespace std;

int main() {
     int cases;
     cin>>cases;
     while(cases--){
         int speed, sg, fg, d, secs;
         cin>>speed>>sg>>fg>>d>>secs;
         double x = 0.0;
         x = (d*50.0)*3.6/secs;
         x += speed;
         if(fabs(sg - x) < fabs(fg-x))
           cout<<"SEBI"<<endl;
         else if(fabs(sg - x) > fabs(fg-x))
           cout<<"FATHER"<<endl;
         else cout<<"DRAW"<<endl;
     }
	return 0;
}
