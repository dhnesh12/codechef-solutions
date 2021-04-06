t = int(raw_input())
for i in range(t):
	st = raw_input().split()
	N = int(st[0])
	A = int(st[1])
	B = int(st[2])
	C = int(st[3])
	A = min(A,N)
	B = min(B,N)
	C = min(C,N)
	L = [A,B,C]
	L.sort()
	R = [0 for x in range(N+1)]
	v = L[2]
	for k in range(v+1):
		R[k] = 1
	# endfor k
	S = [0 for x in range(N+1)]
	tot = 0
	v = L[1]
	for k in range(v+1):
		tot += R[k]
		S[k] = tot
	# endfor k
	for k in range(v+1,N+1):
		tot += R[k] - R[k-v-1]
		S[k] = tot
	# endfor k
	R = [0 for x in range(N+1)]
	tot = 0
	v = L[0]
	for k in range(v+1):
		tot += S[k]
		R[k] = tot
	# endfor k
	for k in range(v+1,N+1):
		tot += S[k] - S[k-v-1]
		R[k] = tot
	# endfor k
	r = 0
	for k in range(N+1):
		r += R[k]
	# endfor k
	print r
# endfor i


