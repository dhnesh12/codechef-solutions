repeat_count = int(input())
while repeat_count > 0:
    j=0
    repeat_count-= 1
    final=""
    k,n= map(int,input().split(" "))
    ret_val= []
    for i in range(k-n-1,k):
        ret_val.append(i+1)
    for i in range(0,k-n-1):
        ret_val.append(i+1)
    for i in ret_val:
        j+=1
        final+=str(i)
        if j<k:
            final+=" "
    print(final)


