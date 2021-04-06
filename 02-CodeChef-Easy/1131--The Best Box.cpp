#include<bits/stdc++.h>
#include<cmath>

using namespace std;

int main(){
    int t;
    cin >> t;
    cout << setprecision(2) << fixed;
    int p,s,i=0;
    double a,b,p4,s2,ps,vol[t];
    while(i<t){
    cin >> p >> s;
    s2 = (double)s/2;
    p4 = (double)p/4;
    ps =4*p4*p4 -12*s2;
    a =(2*p4 - sqrt(ps))/6;
    b = p4 - 2*a;
    vol[i] = a*b*a;
    i++;
}
    for(i=0;i<t;i++){
        cout << vol[i]<<endl;
    }
}
