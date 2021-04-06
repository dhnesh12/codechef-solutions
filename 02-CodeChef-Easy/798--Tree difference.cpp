#include <bits/stdc++.h>
using namespace std;
//int max=200001;
std::vector<int>child[200001] ;
bool hey(){
    for(int i=0;i<200001;i++){
        child[i].clear();
    }
}
bool bfs(int n, bool path[] , bool init[] , int current , int target,std::set<int>&tejus){
    path[current]=true;
    if(current == target){
        init[current]=true;
        path[current]=true;
        tejus.insert(current);
        return true;
    }
    for(int i=0;i<child[current].size();i++){
        int jk=child[current][i];
        if(path[jk]==false){
            
            bool answer=bfs(n,path,init,jk,target,tejus);
            if(answer==true){
                tejus.insert(current);
                init[current]=true;
                return true;
            }
        }
    }
    return false;
}

int main() {
	int t;std::cin >> t;
	while(t--){
	    hey();
	    int n,q;std::cin >> n>>q;
	    int value[n+1];for(int i=1;i<=n;i++)std::cin >> value[i];
	    
	    for(int i=1;i<n;i++){
	        int x,y;cin>>x>>y;
	        child[x].push_back(y);
	        child[y].push_back(x);
	    }
	    while(q--){
	        int a,b;std::cin >> a>>b;
	        bool path[n+1]={false};
	        bool init[n+1]={false};
	        std::set<int>tejus ;
	        bool h=bfs(n,path,init,a,b,tejus);
	        if(h==true){
	            std::vector<int>tempo ;
	            for(int i=1;i<=n;i++){
	                if(init[i]==true){
	                    tempo.push_back(value[i]);
	                }}
	           if(tempo.size()<=100)
	           {int dif=INT_MAX;
	            sort(tempo.begin(),tempo.end());
	            for(int i=1;i<tempo.size();i++){
	                int fg=tempo[i]-tempo[i-1];
	                if(dif>fg){
	                    dif=fg;
	                }
	            }
	            std::cout << dif << std::endl;
	           }
	            else{
	                std::cout << 0 << std::endl;
	            }
	        }
	    }
	}
	return 0;
}
