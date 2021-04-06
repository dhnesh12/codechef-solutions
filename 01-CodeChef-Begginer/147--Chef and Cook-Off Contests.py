tiy=int(input())

#hello
while(tiy>0):
    n=int(input())
    lilly1=[]
    for i in range(0,n):
        str1=input()

        lilly1.append(str1)
    if not (("cakewalk" in lilly1) and ("simple" in lilly1) and ("easy" in lilly1) and ("easy-medium" in lilly1 or "medium" in lilly1) and ("medium-hard" in lilly1 or "hard" in lilly1)) :
        print('No')
    
    else :
        print('Yes')
    tiy=tiy-1