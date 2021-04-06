t = int(input())
for tc in range(t):
    s = input()
    n = len(s)
    ms = set()
    for i in range(n):
        flag=0
        ocnt=0
        ecnt=0
        cnt=0
        for j in range(i,n):
            if s[j] == '1' :
                cnt=cnt+1
                flag=1-flag
            else:
                if flag==1:
                    ocnt=ocnt+1
                else:
                    ecnt=ecnt+1
            
            ms.add((cnt,(ocnt,ecnt)))

    print(len(ms))