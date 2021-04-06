S = set()
S.add(1)
L = []
L.append([1,2])
p = 0
n = 1
while n < 2**30:
	p = n
	n = 2*n+1
	L.append([n,p])
	S.add(n)
# endwhile
t = int(raw_input())
for i in range(t):
	N = int(raw_input())
	if N in S:
		p = 0
		while L[p][0] <> N:
			p += 1
		# endwhile
		r = L[p][1]
	else:
		r = -1
	# endif
	print r
# endfor i

