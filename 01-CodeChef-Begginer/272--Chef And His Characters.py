t=int(input())
for i in range(t):
    s=input()
    c=0
    for j in range(len(s)-3):
        a=[]
        a.append(s[j])
        a.append(s[j+1])
        a.append(s[j+2])
        a.append(s[j+3])
        a.sort()
        if(a[0]=='c' and a[1]=='e' and a[2]=='f' and a[3]=='h'):
            c+=1
    if(c==0):
        print('normal')
    else:
        print('lovely',c)