#include <iostream>
using namespace std;

int main() {
	// your code goes here
	int t;
	cin>>t;
	while(t--){
	    int T[100]={0}, D[100]={0};
	    int t,d,truth,dare;
	    bool checkT=true,checkD=true;
        cin>>t;
        while(t--){
            cin>>truth;
            T[truth] = 1;
        }
        cin>>d;
        while(d--){
            cin>>dare;
            D[dare] = 1;
        }
        cin>>t;
        while(t--){
            cin>>truth;
            if(T[truth] != 1)
                checkT = false;
        }
        cin>>d;
        while(d--){
            cin>>dare;
            if(D[dare] != 1)
                checkD = false;
        }
        if(checkT && checkD)
            cout<<"yes"<<endl;
        else
            cout<<"no"<<endl;
	}
	return 0;
}
