#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
#define i_am_speed() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);


double calc(double b, double c, double x){
    return (x*x + b*x + c)/sin(x);
}



int main(){
    i_am_speed();

    int t; double b, c;
    cin >> t;
    for(int it = 0; it < t; it++) {
        cin >> b >> c;
        double lo = 0, hi = M_PI/2.0;
        for (int im = 0; im < 200; im++){
            double m1 = lo + (hi - lo)/3.0, m2 = hi - (hi - lo)/3.0;
            if (calc(b, c, m1) > calc(b, c, m2)){
                lo = m1;
            }
            else{
                hi = m2;
            }
        }
        cout << fixed << setprecision(10) << calc(b, c, lo) << "\n";
    }
    return 0;
}