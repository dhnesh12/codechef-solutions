# cook your dish here
t=int(input())
for i in range(t):
    f=input()
    b=input()
    k=[]
    p=[]
    m=[]
    k.append(f[0])
    k.append(b[0])
    p.append(f[1])
    p.append(b[1])
    m.append(f[2])
    m.append(b[2])
 #   print(k,p,m)
 
    if ('o' in k and 'b' in p and 'b' in m) or ('b' in k and 'o' in p and 'b' in m) or ('b' in k and 'b' in p and 'o' in m):
        print('yes')
    else:
        print('no')