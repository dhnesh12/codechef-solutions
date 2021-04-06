#include<iostream>
#include <bits/stdc++.h>
using namespace std;

typedef long long LONG;
#define MAX_COUNT 5
#define STR_MAX   11
#define loop(var, start, end)      for(int var = start; var < end; var++)
#define loopwithoutvar(var, start, end) for(var = start; var < end; var++)
//#define loop((type=var), start, end)      for(var = start; var < end; var++)
#define loopdec(var, start, end)   for(int var = start; var >= end; var--)
#define INVALID_32  0xffffffff
#define INVALID INVALID_32



int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int N;
        cin>>N;
        multiset <int> sumset;
        multiset <int> valueSet;
        multiset <int> OldValueSumSet;
        multiset <int> temp;

        int totalSumSets= (1 << N);
        loop(i, 0, totalSumSets)
        {
            int num;
            cin>>num;
            sumset.insert(num);
        }
       
        sumset.erase(0);
        OldValueSumSet.insert(0);
        multiset <int> :: iterator itr,itr2;
        //int cnt=0; 
        while(!sumset.empty())  
        {
            itr = sumset.begin();
            int current = (*itr);
            //cout<<current<<endl;
            valueSet.insert(current);
           // sumset.erase(sumset.find(current));  
            //if(!OldValueSumSet.empty()) 
            {   
                int count = OldValueSumSet.size(); 
                itr2 = OldValueSumSet.begin();
                //temp.insert(OldValueSumSet);
                temp = OldValueSumSet;
                //Old copy to temp multiset
                //temp + current =>insert Old
                for(auto it: temp)
                {
                    
                    int currentSum = current + (it);
                    //cout<<currentSum<<endl;
                    OldValueSumSet.insert(currentSum);
                    sumset.erase(sumset.find(currentSum));                    
                }
                temp.clear();
            }
        //  cnt++;
        //   if(cnt==5)
        //     // break;
           
        }
     
         for(auto it : valueSet)
         {
             cout<<(it)<<" ";
         }
        //  cout<<endl;
        //   for(auto it : OldValueSumSet)
        //   {
        //       cout<<(it)<<" ";
        //   }
         cout<<endl;
    }
    return 0;    
}
