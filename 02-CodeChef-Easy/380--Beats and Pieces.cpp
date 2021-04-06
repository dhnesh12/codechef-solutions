#include<bits/stdc++.h>

using namespace std;

int T , EN , QN , A[200] , arr[200] , tar[200];



int main(){

   // freopen("in.in","r",stdin);

    cin>>T;

    while(T--){

        cin>>EN>>QN;

        for(int j = 1 ; j <= EN ; j++) cin>>A[j];

        vector < pair < int , int > > queries;

        vector < int > perm;

        for(int j = 0 ; j < QN ; j++){
            int a , b;
            cin>>a>>b;
            perm.push_back(j);
            queries.push_back({a , b});
        }

        int ansA = 0 , ansB = 0 , timer = 0;

        do{
            ++ansB;

            for(int j = 1  ; j <= EN ; j++)
                arr[j] = A[j];

            for(int j = 0 ; j < perm.size() ; j++){

                int which = perm[j];

                int len = queries[which].second - queries[which].first + 1;
                int st = queries[which].first , en = queries[which].second;

                for(int i = 0 ; i < len / 2 ; i++){
                    swap(arr[st + i] , arr[en - i]);
                }

            }

            bool ok = 1;

            for(int j = 1 ; j <= EN ; j++){
                if(timer == 0) tar[j] = arr[j];
                else ok &= (arr[j] == tar[j]);
            }

            if(ok) ++ansA;

            ++timer;

        }while(next_permutation(perm.begin() , perm.end()));

        int G = __gcd(ansA , ansB);

        ansA/=G;
        ansB/=G;


        cout<<ansA<<'/'<<ansB<<endl;

    }



}