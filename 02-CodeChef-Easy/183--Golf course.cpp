#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef pair<int,int> pii;
typedef vector<vi> vii;
typedef unordered_map<int,int> umapii;
typedef long long ll;


const int INF = 0x3f3f3f3f;
#define mem(a, b) memset(a, (b), sizeof(a))
#define mod 1000000007
#define mp make_pair
#define pb push_back
#define foreach(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define fi first
#define se second
int main()
{
        std::ios::sync_with_stdio(false);
        cin.tie(NULL);
        int t;
        cin>>t;             // cin.ignore(); must be there when using getline(cin, s)
        for(int i=1;i<=t;i++)
        {
                cout<<"Case "<<i<<":"<<endl;
                int m,n,k;
                cin>>m>>n>>k;
                int arr[m][n];
                for(int j=0;j<m;j++)
                {
                    for(int l=0;l<n;l++)
                        cin>>arr[j][l];
                }
                int maxmat[m][n];
                int cntmat[m][n];
                for(int l=0;l<n;l++)
                {
                        for(int a=0;a<=m-k;a++)
                        {
                            int maxi=arr[a][l];
                            for(int b=a;b<=a+k-1;b++)
                            {
                                    maxi=max(maxi,arr[b][l]);
                            }
                            int cnt=0;
                            for(int b=a;b<=a+k-1;b++)
                            {
                                    if(maxi==arr[b][l])cnt++;
                            }
                            maxmat[a][l]=maxi;
                            cntmat[a][l]=cnt;
                           // cout<<maxmat[a][l]<<" "<<cntmat[a][l]<<endl;
                        }

                }

                 for(int l=0;l<=m-k;l++)
                {
                        for(int a=0;a<=n-k;a++)
                        {
                            int maxi=maxmat[l][a];
                            for(int b=a;b<=a+k-1;b++)
                            {
                                    maxi=max(maxi,maxmat[l][b]);
                            }
                            int cnt=0;
                            for(int b=a;b<=a+k-1;b++)
                            {
                                    if(maxi==maxmat[l][b]) cnt+=cntmat[l][b];
                            }
                            maxmat[l][a]=maxi;
                            cntmat[l][a]=cnt;
                        }

                }
                for(int l=0;l<=m-k;l++)
                {
                        for(int a=0;a<=n-k;a++)
                        {

                                if(cntmat[l][a]>1)
                                    cout<<maxmat[l][a]<<"("<<cntmat[l][a]<<") ";
                                else cout<<maxmat[l][a]<<" ";
                        }
                        cout<<endl;
                }


      }
        
        return 0;
}


