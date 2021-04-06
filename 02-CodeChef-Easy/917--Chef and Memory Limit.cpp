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
	int T,N,i;
	ll S,R;
	cin>>T;
	while(T--){
	    S=0;
	    cin>>N;
	    int M[N];
	    for(i=0;i<N;i++){
	        cin>>M[i];
	    }S=S+M[0];
	    R=M[0];
	    for(i=1;i<N;i++){
	        if(M[i]>R){
	            S=S+(M[i]-R);
	            R=M[i];
	            continue;
	        }if(M[i]<=R){
	            R=M[i];
	        }
	    }cout<<S<<endl;
	}
	return 0;
}