t = int(raw_input())
for i in range(t):
	st = raw_input()
	N = int(raw_input())
	L = []
	for k in range(N):
		st = raw_input().split()
		X = int(st[0])
		Y = int(st[1])
		L.append([X,-Y])
	# endfor k
	L.sort()
	r = 0
	for k in range(1,N):
		dx = L[k][0]-L[k-1][0]
		dy = L[k][1]-L[k-1][1]
		dr = (dx*dx+dy*dy)**0.5
		r += dr
	# endfor k
	print "%.2f" % r
# endfor i

