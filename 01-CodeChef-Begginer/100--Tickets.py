try:
    t=int(input());ans=[]
    for i in range(t):
        s=input()
        a=[]
        for l in s:
            if l not in a:
                a.append(l)
        if len(a)!=2:
            ans.append("NO")
        else:
            f=0
            for l in range(1,len(s)):
                if s[l]==s[l-1]:
                    f=1;break
            if f==1:
                ans.append("NO")
            else:
                ans.append("YES")
    for k in ans:
        print(k)
except:
    pass