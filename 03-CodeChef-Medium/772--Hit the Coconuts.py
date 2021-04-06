T=int(input())
for j in range(T):
	[N,Z]=list(map(int,input().split(' ')))
	A=list(map(int,input().split(' ')))
	A.sort(reverse=True)
	answer=[]
	adder=0
	while(Z!=0):
		temp=[]
		for i in range(len(A)-Z+1):
			temp.append((A[i]*(i+1))+sum(A[i+1:i+Z]))
		answer.append(min(temp)+adder)
		adder+=A[-1]*len(A)
		subtractor=A.pop()
		for i in range(len(A)):
			A[i]-=subtractor
		Z-=1
	print(min(answer))