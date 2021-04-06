#include<iostream>
using namespace std;
typedef long long ll;
int main(){
ll t, C, D, L, x ,y;
cin>>t;

while ( t-- ){
    cin>>C>>D>>L;
    y = D*4 + C*4;
    if(C > 2*D) {x = D*4 + (C - 2*D )*4;}
    else{ x = D*4;}
    
    if( L%4 == 0 && L>=x && L<=y){
    
        cout<<"yes"<<endl;
        
    }
    else{
        cout<<"no"<<endl;
    }
    
    
    
    
    
    
}

    return 0;
}