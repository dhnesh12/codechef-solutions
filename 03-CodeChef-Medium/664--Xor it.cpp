#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,k;
    scanf("%d %d",&n,&k);
	int a[n];
	for(int i=0;i<n;i++)
	    scanf("%d",&a[i]);
	sort(a,a+n);
	int temp = 0,b[25500001];
	for(int i=1;i<n;i++){
	    for(int j=0;i+j<n;j++){
	        if(temp > 10*k)
	            break;
	        b[temp++] = a[j]^a[i+j];
	    }
	}
	sort(b,b+temp);
	for(int i=0;i<k;i++)
	    printf("%d ",b[i]);
	printf("\n");
	return 0;
}
