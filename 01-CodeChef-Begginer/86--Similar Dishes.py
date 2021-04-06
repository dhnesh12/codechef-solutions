# cook your dish here
T=int(input())
for i in range(T):
    A=list(input().split())
    B=list(input().split())
    l1=0
    l2=0
    for j in range(len(A)):
        for k in range(len(B)):
            if(A[j]==B[k]):
                l1+=1
            
    
    if(l1>=2):
        print('similar')
    else:
       print('dissimilar')
        
