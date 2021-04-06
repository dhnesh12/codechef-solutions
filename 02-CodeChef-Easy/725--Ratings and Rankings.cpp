#include<iostream>
using namespace std;
#include<bits/stdc++.h>
#include<vector>

int main(){
    int t;
    cin>>t;
    while(t--){
        int n,m,r=0,count=0,var;
        cin>>n>>m;
        int allrate[n][m];
        int allrank[n][m];
        int ratings[n];
        for(int i=0;i<n;i++){
            cin>>ratings[i];
            
        }
            
        for(int i=0;i<n;i++){
            
            int newrate=ratings[i];
            for(int j=0;j<m;j++){
                cin>>r;
                newrate+=r;
                allrate[i][j]=newrate;
            }
        }
        for(int i=0;i<m;i++){
            vector<int> tmp(n);
            for(int j=0;j<n;j++){
                tmp[j]=allrate[j][i];
            
            }
            sort(tmp.begin(),tmp.end(), greater<int>());
            for(int k=0;k<n;k++){
                
                    auto it=find(tmp.begin(),tmp.end(),allrate[k][i]);
                    allrank[k][i]=(it-tmp.begin())+1;
            }
        }
        for(int i=0;i<n;i++){
                int tmp[m];
                int tmp1[m];
            
            for(int j=0;j<m;j++){
                tmp[j]=(allrate[i][j]);
                tmp1[j]=(allrank[i][j]);
            }
            
            
            int max=*max_element(tmp,tmp+m);
            int min=*min_element(tmp1,tmp1+m);
            int flag=0,index,index1;
            for(int k=0;k<m;k++){
                if(tmp[k]==max){
                     index=k;
                    break;
                }
            }
            for(int k=0;k<m;k++){
                if(tmp1[k]==min){
                    index1=k;
                    break;
                }
            }
            if(index!=index1){
                count++;
            }
          }
        
        
        
        cout<<count<<endl;
        
    }
    return 0;
}