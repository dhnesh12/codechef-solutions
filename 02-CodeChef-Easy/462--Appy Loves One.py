import collections
from collections import defaultdict
import math

def fun(a,k):
   l=0
   ans=0
   for i in range(len(a)):
       if l==0:
          if a[i]==1:
             l+=1  
             
       else:
          if a[i]==1:
              l+=1
          else:
             ans=max(ans,l)
             if ans>=k:
                return k    
             l=0
   ans=max(ans,l)          

   return ans
#for _ in range(int(input())):
#n=int(input())
#s=input()
#n,m=[int(x) for x in input().split()]
n,q,k=[int(x) for x in input().split()]
a=[int(x) for x in input().split()]
s=input()
prev=fun(a,k)  
z=[]  
for x in s:
   if x!='?':
       a = [a[-1]] + a[0:-1]
       
   else: 

      if a[0]==0:
         
         print(prev)
      else:
          prev = (fun(a,k))
          
          print(prev)

  


