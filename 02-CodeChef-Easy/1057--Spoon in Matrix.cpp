#include <iostream>
using namespace std;
#define ll long long
int main() {
	ll t;
	cin>>t;
    while(t--){
        int flag=0;
        ll n , m;
        cin>>n>>m;
        char mat[n][m];
        for(int i = 0;i<n;i++){
            for(int j= 0;j<m;j++){
              cin>>mat[i][j];
            }  
        }
        for(int i = 0;i<n ;i++){
            for(int j = 0;j<m-4;j++){
               if((mat[i][j] == 's' || mat[i][j] == 'S')&&
            (mat[i][j+1] == 'p' || mat[i][j+1] == 'P')&&
            (mat[i][j+2] == 'o'|| mat[i][j+2] == 'O')&&
            (mat[i][j+3] == 'o' || mat[i][j+3] == 'O')&&
            (mat[i][j+4] == 'n' || mat[i][j+4] == 'N')){
              flag = 1; 
              break;
            } 
            }
        }
        if(flag == 1){
             cout<<"There is a spoon!"<<endl;
            continue;
        }
        for(int j = 0;j<m ;j++){
            for(int i = 0;i<n-4;i++){
                if((mat[i][j] == 's' || mat[i][j] == 'S')&&
            (mat[i+1][j]== 'p' || mat[i+1][j] == 'P')&&
            (mat[i+2][j]== 'o' || mat[i+2][j] == 'O')&&
            (mat[i+3][j]== 'o' || mat[i+3][j] == 'O')&&
            (mat[i+4][j]== 'n' || mat[i+4][j] == 'N')){
              flag = 1; 
              break;
            }
            }
        }
        if(flag == 1){
             cout<<"There is a spoon!"<<endl;
            continue;
        }
        if(flag == 0){
        cout<<"There is indeed no spoon!"<<endl;
        }
    }
	return 0;
}
