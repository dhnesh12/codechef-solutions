#include <iostream>
#include <bits/stdc++.h>
using namespace std;

vector<long int> find_subseq(vector<int> &);

int main() 
{
	int i, j, n, num, num_tests, num_elements;
	vector<int> input;
	vector<long int> soln;
	
	cin >> num_tests;
	
	for(i = 0; i < num_tests; ++i)
	{
	    input.clear();
		cin >> num_elements;

		for(j = 0; j < num_elements; ++j)
		{
			cin >> num;
			input.push_back(num);
		}
		
		soln = find_subseq(input);
		n = soln.size();
		cout << soln[0] << endl;
		cout << n - 1 << " ";
		
		for(j = 1; j < n; ++j)
		    cout << soln[j] << " ";
		    
		cout << endl;
	}
	
	return 0;
}

vector<long int> find_subseq(vector<int> &input)
{
    int i, n = input.size(), ptr1 = 0, ptr2 = input.size() - 1;
    long int sum_pos = 0;
    vector<long int> soln;
    
    for(i = 0; i < n; ++i)
    {
        if(input[i] > 0)
            sum_pos += input[i];
    }
    
    soln.push_back(sum_pos);
    
    if(!sum_pos)
        return soln;
        
    while(ptr1 < ptr2)
    {
        if(input[ptr1] <= 0 && input[ptr2] > 0)
        {
            soln.push_back(ptr1 + 1);
            soln.push_back(ptr2 + 1);
            ++ptr1;
            --ptr2; 
            continue;
        }
        
        if(input[ptr1] > 0)
            ++ptr1;
            
        if(input[ptr2] <= 0)
            --ptr2;
    }
    
    if(soln.size() > 1)
        sort(soln.begin() + 1, soln.end());  
        
    return soln;
}