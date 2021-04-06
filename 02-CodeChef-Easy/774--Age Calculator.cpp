#include <iostream>
using namespace std;

int main() {
	// your code goes here
	int t;
	cin>>t;
	while(t--)
	{
	    int months;
	    cin>>months;
	    int days[months];
	    long long int totaldays=0;
	    long long int ans=0;
	    for(int i=0;i<months;i++)
	    {
	        cin>>days[i];
	        totaldays+=days[i];
	    }
	    
	    int birthyear,birthdate,birthmonth,year,month,date;
	    cin>>birthyear>>birthmonth>>birthdate>>year>>month>>date;
	    
	   // ans=(year-birthyear)*totaldays + (year-birthyear)/4;
	    
	    
	    if(year==birthyear)
	    {
	        
	       ans+=days[birthmonth-1]-birthdate+1;
	        if(birthmonth<month)
	        {
	            for(int i=birthmonth+1;i<month;i++)
	            {
	                ans+=days[i-1];
	            }
	           if(month==months && date==days[months-1]+1 && year%4==0)
	                {
	                    ans++;
	                }

	            ans=ans+date;
	            
	        }
	        
	        
	        
    	   // for(int i=birthmonth;i<=months;i++)
    	   // {
    	   //     ans+=days[i-1];
    	   // }
    
    	   // ans=ans-birthdate+1;
    	   
	    }
	    
	    if(year>birthyear)
	    {
	        if(birthyear%4==0)
    	    {
    	        ans++;
    	    }
    
    	    for(int i=birthmonth;i<=months;i++)
    	    {
    	        ans+=days[i-1];
    	    }
    
    	    ans=ans-birthdate+1;
    	    
    	    ans=ans+(year-1-birthyear)*totaldays;
	        for(int i=birthyear+1;i<year;i++)
    	    {
    	        
	            if(i%4==0)
	            {
	                ans++;
	            }
    	    }
    	    
        	   // cout<<ans<<endl;
        	    if(year%4==0 && month==months && date==days[months-1])
        	    {
        	        ans++;
        	    }
        	    	    for(int i=0;i<month-1;i++)
        	    {
        	        ans+=days[i];
        	    }
        	   // cout<<ans<<endl;
        	    ans+=date;
	   
	   
	    }
	    
	    
	    
	    

	    
	    
	    cout<<ans<<endl;
	    
	}
	return 0;
}
