def price_finder(s,k,j):
	if (k==1 and j%2==0) or (k==2 and j%2==1):
		start='G'
		stop='R'
	else:
		start='R'
		stop='G'
	cost=0
	for i in range(0,m):
		if i%2==0 and s[i]!=start:
			if start=='G':
				cost+=5
			else:
				cost+=3
		if i%2==1 and s[i]!=stop:
			if stop=='G':
				cost+=5
			else:
				cost+=3
	return cost




t=int(input())
for asdfg in range(0,t):
	n,m=map(int,input().split())
	costred=0
	costgreen=0
	for j in range(0,n):
		s=input()
		cr=price_finder(s,2,j)
		cg=price_finder(s,1,j)
		costred+=cr
		costgreen+=cg
	print(min(costgreen,costred))