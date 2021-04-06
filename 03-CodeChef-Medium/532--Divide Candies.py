# cook your dish here
def knapsackProblem(items, capacity):
	dp=[[[0,[]] for i in range(capacity+1)] for j in range(len(items)+1)]
	for i in range(1,len(items)+1):
		for j in range(1,capacity+1):
			if items[i-1][1]>j:
				dp[i][j]=dp[i-1][j]
			else:
				if dp[i-1][j][0]>=items[i-1][0]+dp[i-1][j-items[i-1][1]][0]:
					dp[i][j]=dp[i-1][j]
				else:
					dp[i][j][0]=items[i-1][0]+dp[i-1][j-items[i-1][1]][0]
					dp[i][j][1]=dp[i-1][j-items[i-1][1]][1]+[i-1]
	return dp[len(items)][capacity]
	
KS2=[0]
for i in range(1,20):
    candies=[[x**2,x**2] for x in range(1,i+1)]
    T=sum([x**2 for x in range(1,i+1)])
    W=T//2
    ans=knapsackProblem(candies,W)
    bitindex=ans[1]
    bitans=['1']*i
    A=ans[0]
    X=len(bitindex)
    for i in range(X):
        bitans[bitindex[i]]='0'
    KS2.append(''.join(bitans))
def finddif(candies,bits):
    A,B=0,0
    N=len(candies)
    for i in range(N):
        if bits[i]=='1':
            A+=int(candies[i])
        else:
            B+=int(candies[i])
    return abs(A-B)
K=int(input())
for _ in range(int(input())):
    N=int(input())
    if K==2:
        candies=[i**K for i in range(1,N+1)]
        if N<20:
            print(KS2[N])
        else:
            bit=KS2[8+N%8]
            rest=N-(8+N%8)
            rep=rest//8 
            for i in range(rep):
                bit+='10010110'
            if N<8:print(finddif(bit,candies))
            if N>8:
                if N%4==0 or N%4==3:
                    print(0)
                else:
                    print(1)
            print(bit)
    else:
        candies=[int(i**K) for i in range(1,N+1)]
        bitans=['0']*N 
        A=0
        B=0
        Aind=[]
        for i in range(N-1,-1,-1):
            #print(candies[i],A,B)
            if B<A:
                B+=candies[i]
            else:
                A+=candies[i]
                Aind.append(i)
        print(abs(A-B))
        for i in Aind:
            bitans[i]='1'
        print(''.join(bitans))