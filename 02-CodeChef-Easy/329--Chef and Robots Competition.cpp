#include<bits/stdc++.h>
using namespace std;
#define REP(i,a,b) for(int i=a;i<b;i++)
#define vi vector<int>
#define vvi vector<vi>


void printGrid(vvi mat){
    cout<<"GRID:\n";
    for(auto ele:mat){
        for(auto every:ele){
            cout<<every<<" ";
        }
        cout<<endl;
    }
}



bool isValid(int R,int C,int r,int c){
    return r>=0&&r<R&&c>=0&&c<C;
}

void bfs(vvi mat,int R,int C,int sX,int sY,vvi&grid,int k){
    vvi move={
        {1,1},
        {-1,1},
        {1,-1},
        {0,1},
        {1,0},
        {0,-1},
        {-1,0},
        {-1,-1}
    };

    vvi vis(R,vi(C,0));

    deque<pair<int,int>>Q;
    Q.push_back({sX,sY});
    vis[sX][sY]=1;
    grid[sX][sY]=0;

    while(!Q.empty()){

        int x=Q.front().first;
        int y=Q.front().second;
        Q.pop_front();


        for(auto ele:move){
            int beginX=x;
            int beginY=y;
            int start=0;


             int prevX=beginX;
             int prevY=beginY;
            
            while(1){
                prevX=beginX;
                prevY=beginY;
                beginX=beginX+ele[0];
                beginY=beginY+ele[1];
                
                if(isValid(R,C,beginX,beginY)){
                    if(vis[beginX][beginY]==0 && ( abs(beginX-x)+abs(beginY-y)<=k ) && mat[beginX][beginY]==0){
                        vis[beginX][beginY]=1;
                        grid[beginX][beginY]=grid[x][y]+1;
                        Q.push_back({beginX,beginY});
                        
                    }
                }
                else{
                    break;
                }

            }

            // if(prevX!=x||prevY!=y){
            //             Q.push_back({prevX,prevY});
                        
            // }
                    

        }

    
    }

}

int main(){
    int t;
    cin>>t;

    while(t--){
        int n,m,k1,k2;
        cin>>n>>m>>k1>>k2;
        
        
        
        vvi mat(n,vi(m,0));
        
        vvi grid1(n,vi(m,INT_MAX));
        vvi grid2(n,vi(m,INT_MAX));

        int i;
        REP(i,0,n){
            int j;
            REP(j,0,m){
                int ele;
                cin>>ele;
                mat[i][j]=ele;
            }
        }

        // R1 is at (0,0)

        bfs(mat,n,m,0,0,grid1,k1);
        //printGrid(grid1);

        
        // R2 is at (0,m-1)
        
        
        bfs(mat,n,m,0,m-1,grid2,k2);

        //printGrid(grid1);
        //printGrid(grid2);

        vvi finalGrid(n,vi(m,0));

        REP(i,0,n){
            int j;
            REP(j,0,m){
                if(grid1[i][j]==INT_MAX||grid2[i][j]==INT_MAX){
                    finalGrid[i][j]=INT_MAX;
                }
                else{
                    finalGrid[i][j]=max(grid1[i][j],grid2[i][j]);

                }
            }    
        }

        //printGrid(finalGrid);
        int ans=INT_MAX;
        REP(i,0,n){
            int j;
            REP(j,0,m){
                if(finalGrid[i][j]!=INT_MAX){
                    ans=min(ans,finalGrid[i][j]);
                }
            }
        }

        if(ans==INT_MAX||(k1==0&&k2==0))ans=-1;
        cout<<ans<<endl;

    }

    return 0;
}