try:
    t=int(input());ans=[]
    for i in range(t):
        s1=input();s=[]
        for j in s1:
            s.append(j)
        for j in range(len(s)):
            if s[j]=='>':
                s[j]='<'
            elif s[j]=='<':
                s[j]='>'
        cnt=0        
        for j in range(0,len(s)-1):
            if s[j]=='>' and s[j+1]=='<':
                cnt+=1
        ans.append(cnt)
    for l in ans:
        print(l)
except:
    pass