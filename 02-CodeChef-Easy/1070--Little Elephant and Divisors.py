N = 10**3 # value of N required
def primesieve(N):
	n = N+1
	sieve = [True] * (n/2)
	for i in xrange(3,int(n**0.5)+1,2):
		if sieve[i/2]:
			sieve[i*i/2::i] = [False] * ((n-i*i-1)/(2*i)+1)
		# endif
	# endfor i
	return [2] + [2*i+1 for i in xrange(1,n/2) if sieve[i]]
# end fun
primes = primesieve(N)
def gcd(n, m):
	r = n % m
	while r > 0:
		n = m
		m = r
		r = n % m
	#endwhile
	return m
#end fun
t = int(raw_input())
for i in range(t):
	N = int(raw_input())
	st = raw_input().split()
	g = int(st[0])
	k = 1
	while (k < N) and (g > 1):
		n = int(st[k])
		g = gcd(g,n)
		k += 1
	# endwhile
	r = -1
	if g > 1:
		sq = int(g**0.5)
		q = 0
		p = primes[q]
		while (p <= sq) and (g%p > 0):
			q += 1
			p = primes[q]
		# endwhile
		if g%p == 0:
			r = p
		else:
			r = g
		# endif
	# endif
	print r
# endfor i



