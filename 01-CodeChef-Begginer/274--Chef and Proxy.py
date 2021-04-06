import math
t=int(input())
for i in range(t):
    n=int(input())
    s=input()
    count=s.count('P')
    req=math.ceil(n*75/100)-count
    if req<=0:
        print(0)
        continue
    else:
        c=0
        for i in range(2,len(s)-2):
            if s[i-2:i].count('P')>=1 and s[i]=='A' and s[i+1:i+3].count('P')>=1:
                c+=1
    if c>=req:
        print(req)
    else:
        print(-1)