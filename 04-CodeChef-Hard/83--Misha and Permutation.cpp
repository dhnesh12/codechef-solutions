#include<bits/stdc++.h>
using namespace std;
int qq=0;
void subset(int A[], int k, int start, int currLen, bool used[], int length) {

		if (currLen == k) {
                int sum=0;
                int temp[10009];
                int ff=0;
			for (int i = 0; i < length; i++) {
				if (used[i] == true) {
                    temp[ff]=A[i];
					sum+=temp[ff];
                    ff++;
				}
			}
			int maxi=temp[ff-1];
			sum-=maxi;
			if(sum>maxi)
                qq++;
			return;
		}
		if (start == length) {
			return;
		}
		used[start] = true;
		subset(A, k, start + 1, currLen + 1, used,length);
		used[start] = false;
		subset(A, k, start + 1, currLen, used,length);
	}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin>>t;
    while(t--)
    {
        int n,i,k;
        cin>>n>>k;
        int arr[100099];
        for(i=0;i<n;i++)
        {
            arr[i]=i+1;
        }
		bool B[100099]={0};
		subset(arr, k, 0, 0, B, n);
		cout<<qq<<endl;
		qq=0;
    }
    return 0;
}
