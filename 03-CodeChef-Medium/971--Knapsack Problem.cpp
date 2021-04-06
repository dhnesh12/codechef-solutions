#include <bits/stdc++.h>
using namespace std;

int main() {
    long long int n;cin>>n;
    long long int sum=0;
    vector<long long int> one, two;
    for(int i=0;i<n;i++)
    {
        long long int a,b;
        cin>>a>>b;
        if(a==1)
        one.push_back(b);
        else 
        two.push_back(b);
        sum+=a;
    }
    //cout<<sum<<endl;
    long long int s1=one.size(),s2=two.size();
    sort(one.begin(),one.end(),greater<int>());
    sort(two.begin(),two.end(),greater<int>());
    long long int c=0,c1=0,c2=0,j=0,k=0,flag=0;
    //k-> pointer for two array and j->  pointer for 1 error
    long long int dp[sum+1]={0};
    for(long long int i=2;i<=sum;i+=2)
    {
        c1=0,c2=0,flag=0;
        if(k<s2)
        {
            c2+=two[k];
        }
        if(j+1<s1)
        {
            c1+=one[j]+one[j+1];
        }
        else if(j< s1){
			c1+= one[j];
			flag= 1;
		}
       	if(c2>c1){
			c+= c2;
			k++;
		}
		else{
			if(flag== 1){
				c+= c1;
				j+= 1;
			}
			else{
				c+= c1;
				j+= 2;
			}
		}
		dp[i]= c;
    }
    
    j=0,c=0,k=0;
    if(s1>=1)
    {
        c=one[j];
        j++;
        dp[1]=c;
    }
    for(int i=3;i<=sum;i+=2){
         c1= 0, c2= 0, flag= 0;
		if(k<s2) {
				c2+= two[k];
		}
		if(j+ 1 < s1){
				c1+= one[j]+ one[j+ 1];
			
		}
		else if(j< s1){
			c1+= one[j];
			flag= 1;
		}
		if(c2> c1){
			c+= c2;
			k++;
		}
		else{
			if(flag== 1){
				c+= c1;
				j+= 1;
			}
			else{
				c+= c1;
				j+= 2;
			}
		}
		dp[i]= c;
    }
	for(int i= 1; i<= sum; i++){
		cout<<dp[i]<<" ";
	}
	cout<<endl;
    
    
    
    
    
    
    
    
    // //cout<<n<<" "<<sum<<endl;
    // long long int knap[n+1][sum+1];
    // for(int i=0;i<=n;i++) knap[i][0]=0;
    // for(int i=0;i<=sum;i++) knap[0][i]=0;
    // for(int i=1;i<=n;i++)
    // {
    //     for(int j=1;j<=sum;j++)
    //     {
    //         if(wt[i-1]<=j)
    //             knap[i][j]=max(val[i-1]+knap[i-1][j-wt[i-1]], knap[i-1][j]);
    //         else
    //             knap[i][j]=knap[i-1][j];
    //     }
    // }
    // for(int i=1;i<=sum;i++)
    //     cout<<knap[n][i]<<" ";
    // cout<<endl;
    
	// your code goes here
	return 0;
}
