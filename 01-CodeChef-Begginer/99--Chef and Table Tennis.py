# cook your dish here
n=int(input())
for i in range(n):
    st=input()
    c1=0 
    c0=0 
    for i in st:
        if(i=='1'):
            c1+=1
        else:
            c0+=1
    if(c1>c0):
        print('WIN')
    else:
        print("LOSE")