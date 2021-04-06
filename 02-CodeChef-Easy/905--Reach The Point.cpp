/*
                       _oo0oo_
                      o8888888o
                      88" . "88
                      (| -_- |)
                      0\  =  /0
                    ___/`---'\___
                  .' \|     |// '.
                 / \|||  :  |||// \
                / _||||| -:- |||||- \
               |   | \  -  /// |   |
               | \_|  ''\---/''  |_/ |
               \  .-\__  '-'  ___/-. /
             ___'. .'  /--.--\  `. .'___
          ."" '<  `.___\_<|>_/___.' >' "".
         | | :  `- \`.;`\ _ /`;.`/ - ` : | |
         \  \ `_.   \_ __\ /__ _/   .-` /  /
     =====`-.____`.___ \_____/___.-`___.-'=====
                       `=---='
 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
              Codes for Sky Task @Codechef
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include<bits/stdc++.h>
#include<cstring>
//#define Sky's Code
#define   ll         long long
#define   ull        unsigned long long
#define   pb         push_back
#define   ff         first
#define   ss         second
#define   all(v)     (v.begin(), v.end())
#define   rall(v)    (v.rbegin(), v.rend())
#define   pi         acos(-1.0)
#define   FastRead   ios_base::sync_with_stdio(0);cin.tie(0); cout.tie(0);
#define   bug(a)     cerr << #a << " : " << a << endl
using namespace std;

int main() {
	//code
	int T;
	ll X,Y,A,B,P,Q,Z,M,N;
	cin>>T;
	while(T--){
	    cin>>X>>Y;
	    if(X<0){
	        X=X*(-1);
	    }if(Y<0){
	        Y=Y*(-1);
	    }if(X<=Y){
	        A=X;
	        B=Y;
	    }else{
	        A=Y;
	        B=X;
	    }P=A*2;
	    Z=B-A;
	    M=Z/2;
	    N=Z/2;
	    if(B==X){
	        if(Z%2==1){
	           M++;
	        }
	    }if(B==Y){
	        if(Z%2==1){
	           N++;
	        }
	    }Q=P+(3*M)+N;
	    cout<<Q<<endl;
	}
	return 0;
}