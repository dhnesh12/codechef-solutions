t = int(raw_input())
for i in range(t):
	st = raw_input().split()
	DS = int(st[0])
	DT = int(st[1])
	D = int(st[2])
	L = [D,DS,DT]
	L.sort()
	r = L[2]-L[1]-L[0]
	if r < 0:
		r = 0
	# endif
	print r
# endfor i


