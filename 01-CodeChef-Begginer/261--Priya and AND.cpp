#include<iostream>
using namespace std;
int main()
{
    int T;
    cin>>T;
    while(T--){
        int N;
        cin>>N;
        int A[N],l,count;
        count=0;
        for(int i=1;i<=N;i++){
            cin>>A[i];
        }
        for(int i=1;i<N;i++){
            l=A[i];
            for(int j=i+1;j<=N;j++){
                if((l&A[j])==l){
                    count++;
                }
            }
        }
        cout<<count<<endl;
    }
    return 0;
}
