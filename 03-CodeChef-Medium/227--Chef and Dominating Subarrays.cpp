#include<bits/stdc++.h>
using namespace std;
int a[1000099];

int sum=0;

int findCandidate(int *, int);
bool isMajority(int *, int, int);
  
/* Function to print Majority Element */
void printMajority(int a[], int size)
{
  /* Find the candidate for Majority*/
  int cand = findCandidate(a, size);
  
  /* Print the candidate if it is Majority*/
  if(isMajority(a, size, cand))
    sum++;
  //else
    //printf("NO Majority Element");
}
  
/* Function to find the candidate for Majority */
int findCandidate(int a[], int size)
{
    int maj_index = 0, count = 1;
    int i;
    for(i = 1; i < size; i++)
    {
        if(a[maj_index] == a[i])
            count++;
        else
            count--;
        if(count == 0)
        {
            maj_index = i;
            count = 1;
        }
    }
    return a[maj_index];
}
  
/* Function to check if the candidate occurs more than n/2 times */
bool isMajority(int a[], int size, int cand)
{
    int i, count = 0;
    for (i = 0; i < size; i++)
      if(a[i] == cand)
         count++;
    if (count > size/2)
       return 1;
    else
       return 0;
}

int main()
{
    int n;
    cin>>n;
    map<int,int>mtp;
    //int sum=0;
    for(int i=0;i<n;i++)
        cin>>a[i];
    for(int i=0;i<n;i++)
    {
        for(int j=i;j<n;j++)
        {
        	int arr[100099];
        	int c=0;
        	for(int k=i;k<=j;k++)
        	{
        		arr[c++]=a[k];
        	}
        	printMajority(arr,j-i+1);
        }
    }
    cout<<sum<<endl;
    return 0;
 
}