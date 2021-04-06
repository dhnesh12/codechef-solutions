# cook your dish here
# cook your dish here
t = int(input())
for _ in range(t):
    n = int(input())
    s = input()
    place=0
    i = 0
    done = 0
    ans=0
    while i<n and s[i]=="#":
        done+=1
        i+=1
    place=done
    sub= done-1
    for k in range(done+1,n):
        if s[k]=="#":
            sub=max(sub+2,k)
            if sub>=n-1:
                ans=-1
                break
            ans+= abs(place-sub)+abs(sub-k)
            place+=1
    print(ans)        
            