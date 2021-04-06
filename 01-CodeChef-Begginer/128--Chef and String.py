c=0
h=0
e=0
f=0
for i in input():
    if i=='C':
        c=c+1
    elif i=='H' and c>0:
        h=h+1
        c=c-1
    elif i=='E' and h>0:
        e=e+1
        h=h-1
    elif i=='F' and e>0:
        f=f+1
        e=e-1
print(f)