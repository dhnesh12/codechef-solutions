# include<iostream>
using namespace std;

int main(){
    long long int n, k;
    cin>>n>>k;
    long long int a[n];
    long long int max , min;
    cin>>a[0];
    max = a[0];
    min = max;
    for(long long int i = 1 ; i < n ; i++){
        cin>>a[i];
        if(a[i] > max){
            max = a[i];
        }
        
        if(a[i] < min){
            min = a[i];
        }
    }
    
    if(k == 0){
        for(long long int i = 0; i < n ; i++){
            cout<<a[i]<<" ";
        }
        return 0;
    }
    // first loop
    for(long long int i = 0; i < n ; i++){
        a[i] = max - a[i];
    }
    
    max = max - min;

    if(k%2 == 1){
        for(long long int i = 0; i < n ; i++){
            cout<<a[i]<<" ";
        }
    }else{
        for(long long int i = 0; i < n ; i++){
            cout<<max - a[i]<<" ";
        }
    }
}