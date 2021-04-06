#include <iostream>
#include <bits/stdc++.h>
#define boost ios::sync_with_stdio(false); cin.tie(0)

using namespace std;

long long pivot_val(long long n)
{
    long double piv = n;
    return (long long )( ((-2.0) + (sqrt(4.0 + 8*(piv*piv+piv)))) /4.0);
}

// to get total number of internal swaps we have to calculate the 
// different combinations

long long nC2(long long n)
{
    return (n*(n - 1))/2;
}
int main(void) 
{
    boost;
    int test_size;
    cin>>test_size;
    while(test_size--)
	{
	    long long size;
	    cin>>size;
	    // check if sum of numbers till size 
	    // is odd or even
	    // if odd then the number of partition
	    // or number of clean swaps are 0
	    // else if even then no problem
	    // sum of n numbers : [n*(n+1)]/2
	    if( ((size*(size + 1))/2) %2 != 0)
	    {
	        cout<<"0"<<"\n";
	        // and skip this loop as no calculation
	        // to do
	        continue;
	    }
	    //if even we have to find the pivot element
	    // which will determine the number 
	    // of nice swaps we can do
	    // create a pivot element
	    
	    // the ideal pivot will be one were the 
	    // sum of elements upto pivot 
	    // equals sum of elements after pivot
	    
	    // so sum upto pivot element will be half
	    // of total sequence sum
	    
	    // if pivot is x and total elements are N
	    /*
sum upto x element : [x*(x+1)]/2 
sum of N elements : sum = [N*(N+1)]/2

therefore ideal pivot is when 
[x*(x+1)]/2  == sum / 2

if we solve this quadractic equation we can find x
that is the pivot value.
	    */
	    long long pivot,nos_swaps=0;
	    //find pivot element of sequence of length "size"
	    pivot = pivot_val(size);
	    //once we have the pivot we can say that we will get at
        // minimum  (size - pivot) swaps 
        nos_swaps += size - pivot;
        
        // now check if sum of first elements upto pivot 
        // are equals to last elements from pivot
        //then we can have internal swaps in the first half before pivot
        // and next internal swaps in the second half after pivot
/*
number of swaps before pivot: 
pivot choose 2

number of swaps after pivot till end of size:

(size-pivot) choose 2

once we get these nice swaps from the different combinations 
we add it also to the final number of nice swaps

*/        

    if(2*(pivot*pivot + pivot) == (size*size + size))
    {
        nos_swaps += nC2(pivot) +nC2(size-pivot);
    }
    cout<<nos_swaps<<"\n";
	   
	}
	return 0;
}

