#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

int N;
vector<int>graph[40000];

bool bpm(int u, int seen[], int matchR[],int matchL[]){ 

    for (int v = 0; v < graph[u].size(); v++){ 
        if (!seen[graph[u][v]]){ 
            seen[graph[u][v]] = 1;  
            if (matchL[graph[u][v]]< 0 || bpm( matchL[graph[u][v]], seen, matchR, matchL)){ 
                matchR[u] = graph[u][v]; 
                matchL[graph[u][v]] = u;
                return true; 
            } 
        } 
    } 
    return false; 
} 
  



void addright(int address){
    if(address%N!=N-1){
        graph[address].push_back(address+1);
    }
    
}
void addleft(int address){
    if(address%N!=0){
        graph[address].push_back(address-1);
    }
}
void addup(int address){
    if(address>N-1){
        graph[address].push_back(address-N);
    }
}
void adddown(int address){
    if(address<N*(N-1)){
        graph[address].push_back(address+N);
    }
}


int main(){
    int t;
    cin>>t;
    while(t--){

        int n;
        cin>>n;
        N=n;
        
        int matchR[n*n];
        int matchL[n*n];
        
        
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                int address=(i*n)+j;
                graph[address].clear();
                matchR[address]=-1;
                matchL[address]=-1;
                char s[10];
                cin>>s;
                for(int k=0;k<strlen(s);k++){
                    
                    if(s[k]=='R'){
                        addright(address);
                    }
                    else if(s[k]=='L'){
                        addleft(address);
                    }
                    else if(s[k]=='U'){
                        addup(address);
                    }
                    else{
                        adddown(address);
                    }
                }
            }
        }
        
        
        int result=0;
        
        int temp = -1;  
        while(result!=temp && result<n*n){
            temp = result;
            int seen[n*n]; 
            memset(seen, 0, sizeof(seen)); 
            for (int u = 0; u<n*n; u++){ 
                if (matchR[u]==-1 && bpm(u, seen, matchR, matchL)){
                    result++; 
                } 
            } 
        }
        
        if(result>=n*n){
            cout<<"YES"<<endl;
            int count=0;
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    int address=(i*n)+j;
                    int temp;
                    temp=matchR[address]-address;
                    if(temp==1){
                        cout<<"R"<<" ";
                    }
                    else if(temp==-1){
                        cout<<"L"<<" ";
                    }
                    else if(temp==n){
                        cout<<"D"<<" ";
                    }
                    else{
                        cout<<"U"<<" ";
                    }
                    
                    if(address%n==n-1){
                        cout<<endl;
                    }
                }
            }
        }
        else{
            cout<<"NO"<<endl;
        }
        
    }
	// your code goes here
	return 0;
}