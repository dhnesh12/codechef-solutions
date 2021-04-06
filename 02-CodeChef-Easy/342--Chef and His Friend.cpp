#include <iostream>
using namespace std;

int main() {
    int t;cin>>t;
    while(t--){
        double a1,b1,t1,t2;cin>>a1>>b1>>t1>>t2;
        double d=a1,e=t1;
        if(a1>b1){a1=b1;t1=t2;t2=e;b1=d;}
        double ans=0;
        if(a1<t2){
            ans+=double(a1/(2.0*b1));
        }
        else{
            ans+=double((t2*t2)/(2.0*a1*b1))+double(((a1-t2)*(t2))/(a1*b1));
        }
        if(t1<(b1-a1)){
            ans+=double(t1/b1);
        }
        else if(t1>=(b1)){
            ans+=double(1.0-(a1/(2*b1)));
        }
        else{//if(ans>0){cout<<"uil"<<endl;}
            ans+=(b1-t1)*(t1)/(b1*a1);//cout<<"hgl";
            //if(ans>0){cout<<"JKL";}
            ans+=0.5*(t1+b1-a1)*(a1-b1+t1)/(a1*b1);
        }
        cout<<ans<<endl;
    }
	// your code goes here
	return 0;
}
