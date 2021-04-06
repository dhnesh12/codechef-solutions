t=int(input())
while(t):
    t-=1 
    s=input()
    s=list(s)
    a=0
    b=0
    for i in range(len(s)):
        if(s[i]=='a'):
            a+=1 
        if(s[i]=='b'):
            b+=1 
    if(a==len(s) or b==len(s)):
        print(0)
    else:
        if(a<b):
            print(a)
        else:
            print(b)