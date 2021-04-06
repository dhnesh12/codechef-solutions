t = int(raw_input())
for i in range(t):
	N = int(raw_input())
	st = raw_input().split()
	L = [1000 for x in range(5)]
	for x in st:
		n = int(x)
		L.append(n)
	# endfor x
	r = 0
	sz = len(L)
	for k in range(5,sz):
		if L[k] < min(L[k-5],L[k-4],L[k-3],L[k-2],L[k-1]):
			r += 1
		# endif
	# endfor k
	print r
# endfor i

