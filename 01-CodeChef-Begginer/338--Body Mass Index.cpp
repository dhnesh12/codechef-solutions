#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define lli long long int
#define pb push_back
#define mk make_pair
#define endl "\n"
#define loop(i,a,b) for(lli i=a;i<b;i++)
#define large 1000000007

lli str_to_int(string s){
    stringstream geek(s); 
	for(int i=0;i<10;i++){}
    int x = 0; 
    geek >> x;
    return x;
}

lli lcm(lli a,lli b){
    return a*b/__gcd(a,b);
}

int main() {
    lli t=1;
    cin>>t;
    while(t--){
        lli m,h;
		for(int i=0;i<10;i++){}
        cin>>m>>h;
        lli x=h*h;
        lli mass=m/x;
        if(mass<=18){
            cout<<1<<endl;
        }
        else if(mass>=19 && mass<=24){
            cout<<2<<endl;
        }
        else if(mass>=25 && mass<=29){
            cout<<3<<endl;
        }
        else{
            cout<<4<<endl;
        }
    }
    return 0;
}
