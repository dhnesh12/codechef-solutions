#include <bits/stdc++.h>

using namespace std;

//std::vector<std::vector<int> > custMatrix(500, std::vector<int>(500,500));
//int customerData[105][105];

//budgetMat index is the starting point
//in pairs first = destination, second = budget


int  mod(int x, int y)
{
  if(x<y)
  return x;
  return y & (y-1) ? x % y : x & (y-1);
}



int verifyRevenue(vector<vector<pair<int,int> > > budgetMat, int *tolls,int Nodes,int custCount){
	int totalRevenue=0;

	/*cout<<"Tolls: ";
	for(int i=0;i<Nodes;i++)
		cout<<tolls[i]<<" ";
	cout<<endl;
    //*/

	for(int i=1;i<Nodes;i++){
		
		vector<pair<int,int> > paths = budgetMat[i];
		vector<pair<int,int> >::iterator ptr;
		for(ptr = paths.begin();ptr < paths.end();ptr++){

			int dest   = ptr->first;
			int budget = ptr->second;
			//cerr<<" From:"<<i<<" To : "<<dest<<" Budget : "<<budget<<endl;
			
			int cost = 0;
			for(int j=i-1;j<(dest-1);j++){
				cost += tolls[j];
			}
			//cerr<<"Estimated Cost:"<<cost<<endl;

			if(cost <= budget)
				totalRevenue += cost;
		}
	}
	return totalRevenue;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
	int T;
	cin>>T;
	int times = time(0);
	
	std::vector<pair<int,int>> costArrayGenerated(200);

	while(T--){
	srand(T*times+10504);
		int N,M;
		cin>>N>>M;
        vector<vector<pair<int,int> > > budgetMat(500);
		

		
		/*for(int i=0;i<105;i++){
			for(int j=0;j<105;j++)
				customerData[i][j] = 0;
		}*/

		/*for(int i=1;i<=100;i++){
			for(int j=1;i<=100;i++){
				custMatrix[i][j] = 0;
			}
		}*/

		int min=1000000,max=0;

		for(int i=1;i<=M;i++){
			int S,E,B;
			cin>>S>>E>>B;

			//customerData[S][E] = B; 

			/*for(int j=S;j<E;j++){
				custMatrix[i][j] = B/((S+E)/2);
			}*/

			if(B<min)
				min = B;
			if(B>max)
				max = B;

			pair<int,int> elem = make_pair(E,B);
			budgetMat[S].push_back(elem);
			//}
		}

		//max,min pairs
		//std::vector<pair<int,int> > costArray(N+1);

		/*for(int i=1;i<N;i++){
			int max=0,min=1000000;
			for(int j=1;j<=M;j++){
				if(custMatrix[j][i]>max)
					max = custMatrix[j][i];
				if(custMatrix[j][i]<min)
					min = custMatrix[j][i];
			}

			costArray[i]=make_pair(max,min);
		}
		*/

		int FinalTolls[102]={0};
		
		
        max = max/(N);
	min = min/(N+log(N)*10);
	    
	    int realMax = max;
	    int realMin = min;
	    
        int tries = 18000;
        int minTries = 8000;
        
        if(N<10)
            minTries = 30000;
            else
        if(N<15)
            minTries = 10000;
        else
          if(N<30)
            minTries = 10000;
            else 
            if(N<50)
            minTries =  10000;
            else 
            if(N<75)
             minTries = 8000;
        
        

		int maxRev = 0;
		
		std::vector<pair<int,int>> costArrayGeneratedTemp(200);
		for(int i=1;i<N;i++){
		    costArrayGenerated[i].second = min;
		    costArrayGenerated[i].first  = max;
		}
		
		while(minTries--){
			
			int tolls[102] = {0};
			
            
			for(int i=1;i<N;i++){
			    max = costArrayGenerated[i].first;
			    min = costArrayGenerated[i].second;
			    
			    if(maxRev&1){
				    max = realMax;
				    min = realMin;
				}

				int divider = max - min + 1;
				int mid = (max + min)/2;
				
				
				//generate random values between minC - mid and mid - maxC
				//divider =(max + min)/2 + 1;
				//int newMinC = min + rand()%divider;
				//int newMaxC = mid + rand()%divider;
				int newMinC = min + mod(rand(),divider);
				divider = max - newMinC + 1;
				
				int newMaxC = newMinC + mod(rand(),divider);

				divider =(newMaxC + newMinC)/2;
				if(divider==0)
					divider = 1;
					
				int x = (rand()%5);
				if(x==2){
				    divider = 0;
				    newMinC = 0;
				    newMaxC = 0;
				}
				int value = divider;
				costArrayGeneratedTemp[i].second = newMinC;
				costArrayGeneratedTemp[i].first  = newMaxC;
				//cout<<" >> "<<costArray[i].second<<" "<<costArray[i].first<<" "<<value<<endl;
				tolls[i-1]=value;
			}
			

			int rev =  verifyRevenue(budgetMat,tolls,N,M);
			//cout<<rev<<endl;
			if(rev>maxRev){
				maxRev = rev;
				
				  
				for(int j=1;j<N;j++){
					costArrayGenerated[j].second = costArrayGeneratedTemp[j].second;
					costArrayGenerated[j].first  = costArrayGeneratedTemp[j].first;
				}
			}
		}

		//zero check.
		minTries = 100;

		for(int i=1;i<N;i++){
			FinalTolls[i-1] = (costArrayGenerated[i].second+costArrayGenerated[i].first)/2;
		}
		
		while(minTries--){
			
			int tolls[102] = {0};
			
            
			for(int i=1;i<N;i++){
			    int value = FinalTolls[i-1];
			    int x = (rand()%7);

			    if(x==1){
			    	value = 0;
			    }
				//cout<<" >> "<<costArray[i].second<<" "<<costArray[i].first<<" "<<value<<endl;
				tolls[i-1]=value;
			}
			

			int rev =  verifyRevenue(budgetMat,tolls,N,M);
			//cout<<rev<<endl;
			if(rev>maxRev){
				maxRev = rev;
				
				  
				for(int j=1;j<N;j++){
					costArrayGenerated[j].second = tolls[j-1]/2;
					costArrayGenerated[j].first  = tolls[j-1]/2;
				}
			}
		}


		maxRev = 0;
		tries = 1;

		while(tries--){
			int tolls[102] = {0};
			for(int i=1;i<N;i++){
			    
			    
				int divider =(costArrayGenerated[i].second + costArrayGenerated[i].first)/2;
				if(divider==0)
					divider = 1;
				//srand(time(0));
				int value = divider;
				//cout<<">>>>"<<min<<"   "<<max<<"  "<<value<<endl;
				//cout<<" >> "<<costArray[i].second<<" "<<costArray[i].first<<" "<<value<<endl;
				tolls[i-1] = value;
			}

			int rev =  verifyRevenue(budgetMat,tolls,N,M);
			//cout<<rev<<endl;
			if(rev>maxRev){
				for(int i=1;i<N;i++){
					FinalTolls[i-1] = tolls[i-1];
				}
				maxRev = rev; 
			}

		}

		for(int i=0;i<N-1;i++){
				cout<<FinalTolls[i]<<" ";
		}
		cout<<endl;


	}

}