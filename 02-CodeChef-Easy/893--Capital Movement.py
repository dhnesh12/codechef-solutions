from collections import defaultdict as dd
for _ in range(int(input())):
	n = int(input())
	ppl = list(map(int,input().split()))
	teleport = dd(lambda : set())
	for _ in range(n-1):
		u,v = map(int,input().split())
		teleport[u].add(v)
		teleport[v].add(u)
	arr = sorted(enumerate(ppl), key=lambda x : (x[1],x[0]), reverse=True)
	res = ['']*n
	for i in range(1,n+1):
		capital = 0
		for num,j in arr:
			num += 1
			if num != i and num not in teleport[i]:
				capital = num
				break
		res[i-1] = str(capital)
	print(' '.join(res))