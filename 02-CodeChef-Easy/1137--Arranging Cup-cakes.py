import math
import sys 
t=int(input())
while(t>0):
    n=int(input())
    diff=sys.maxsize
    end=int(math.sqrt(n))
    for i in range(1,end+1):
        if(n%i==0):
            s=n/i
            diff=min(diff,abs(i-s))
        
    print(int(diff))
    t=t-1