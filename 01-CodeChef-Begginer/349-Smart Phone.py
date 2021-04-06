t=int(input())
l=[]
for i in range(t):
    n=int(input())
    l.append(n)
l.sort()
j=0
p=[]
for x in l:
    u=x*(t-j)
    p.append(u)
    j=j+1 
p.sort()
print(p[t-1])
