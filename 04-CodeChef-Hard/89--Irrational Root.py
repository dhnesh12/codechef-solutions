P=10**9+7
 
from math import ceil, log
 
#---Polynomials are arrays p(x) = sum_{i=0}^n a_i x^i is entered as 
#---[a_0, a_1, ... , a_n]
#---Polynomial addition 
 
def addpolymod(p,q):
    l=max(len(p),len(q))
    r=p+[0]*(l-len(p))
    s=q+[0]*(l-len(q))
    return [(r[i]+s[i])%P for i in range(l)]
 
#---Naive multiplication of polynomials 
 
def multpolymod(p,q):
    l=len(p)+len(q)-1
    r=[0]*l
    if len(p)<=len(q):
        for i in range(len(p)):            
            for j in range(i,i+len(q)):
                r[j]=(r[j]+p[i]*q[j-i]%P)%P
    else:
        for i in range(len(q)):           
            for j in range(i,i+len(p)):
                r[j]=(r[j]+q[i]*p[j-i]%P)%P
    return r
    
#---Euclidean extended gcd algorithm 
 
def xgcd(b,n):
    x0,x1,y0,y1=1,0,0,1
    while n!= 0:
        q,b,n=b//n,n,b%n
        x0,x1=x1,x0-q*x1
        y0,y1=y1,y0-q*y1
    return b,x0,y0
 
#---Finds modular inverse when the inverse exists (g=1) : g, x, y satisfy g=ax+my
 
def modinv(a,m):
    g,x,y=xgcd(a,m)
    return x%m
 
#---Pre-computing powers of 2, factorials mod P, and inverse factorials mod P
 
p1=380*2**15+1
p2=404*2**15+1
p3=756*2**15+1
BIG=p1*p2*p3
primess=[p1,p2,p3]
unitroot={p1:623,p2:498,p3:770}
PP=[0,0,0]
PP[0]=modinv(p2*p3,p1)*p2*p3%BIG
PP[1]=modinv(p1*p3,p2)*p1*p3%BIG
PP[2]=modinv(p1*p2,p3)*p1*p2%BIG
 
w=[[],[],[]]  
wi=[[],[],[]]
m=[]
mi=[[],[],[]]
 
for i in range(17):
    m.append(1<<i)  #--precomputing power of 2
    for j in range(3):
        w[j].append(pow(unitroot[primess[j]],1<<(16-i),primess[j])) #--- w[i] is 2**i th root of unity
        wi[j].append(modinv(w[j][i],primess[j])) #--- wi[i] is inverse of w[i]
        mi[j].append(modinv(m[i],primess[j])) #--inverse of power of 2 mod P
 
fact=[1]
infact=[1]
MAX=m[14]+1
temp=1
intemp=1
 
for i in range(1,MAX):
    temp=(temp*i)%P
    intemp=(intemp*modinv(i,P))%P
    fact+=[temp]
    infact+=[intemp]
 
def nspot(l):
    return int(ceil(log(l,2)))
 
def chinese_remainder(K):
    ans=0
    for i in range(3):
        ans=(ans+(K[i]*PP[i])%BIG)%BIG
    return ans%P
  
def fft(t,p,i):
    if len(p)==1:
        return [p[0]]*m[t]
    a = fft(t-1,p[0::2],i)
    b = fft(t-1,p[1::2],i)
    ret = [0]*m[t]
    x = 1
    for k in range(m[t-1]):
        ret[k] = (a[k]+x*b[k])%primess[i]
        ret[k+m[t-1]] = (a[k]-x*b[k])%primess[i]
        x = x*w[i][t]%primess[i]
    return ret
    
def ifft(t,p,i):
    if len(p)==1:
        return [p[0]]*m[t]
    a = ifft(t-1,p[0::2],i)
    b = ifft(t-1,p[1::2],i)
    ret = [0]*m[t]
    x = 1
    for k in range(m[t-1]):
        ret[k] = (a[k]+x*b[k])%primess[i]
        ret[k+m[t-1]] = (a[k]-x*b[k])%primess[i]
        x = x*wi[i][t]%primess[i]
    return ret
 
def square(t, p1,i):
    a = fft(t, p1,i)
    p3 = [(a[k]*a[k])%primess[i] for k in range(m[t])]
    final = ifft(t, p3,i)
    return [(x*mi[i][t])%primess[i] for x in final]
 
def squarefast(p):
    l=2*len(p)-1
    k=nspot(l)
    Y=[square(k,p,j) for j in range(3)]  
    return [chinese_remainder([Y[0][i],Y[1][i],Y[2][i]]) for i in range(l)]
 
def squarepoly(p):
    l=2*len(p)-1
    if len(p)<17:
        return multpolymod(p,p)
    return squarefast(p)
        
def ftrans(f,t):
    lf=len(f)          
    #---fft expansion of f(x+sqrt(t))---       
    fn=[fact[lf-1-i]*f[lf-1-i]%P for i in range(lf)]        
    gn=[infact[i]*pow(t,i//2,P)%P for i in range(lf)]
    dlf=2*(lf-1)       
    ResH=[0]*(lf-1)+[(fn[-1]*gn[0]%P+gn[-1]*fn[0]%P)%P]
    del fn[-1]
    del gn[-1]
    H=[0]*(lf+1)
    if lf<63:
        #H=multpolymod(fn,gn)
        H1=multpolymod(fn[0::2],gn[0::2])+[0]*2
        H2=multpolymod(fn[0::2],gn[1::2])+[0]*2
        for i in range(1+(lf-1)//2):
            H[2*i]=H1[i]
            H[2*i+1]=H2[i]
    else:
    	l=lf-2
    	k=nspot(l)
    	fftfn=[fft(k,fn[0::2],j) for j in range(3)]
    	fftgne=[fft(k,gn[0::2],j) for j in range(3)]
    	fftgno=[fft(k,gn[1::2],j) for j in range(3)]
    	pointwise=[[fftfn[j][i]*fftgne[j][i]%primess[j] for i in range(m[k])] for j in range(3)]
    	pointwiso=[[fftfn[j][i]*fftgno[j][i]%primess[j] for i in range(m[k])] for j in range(3)]
    	ifftpwe=[[mi[j][k]*x%primess[j] for x in ifft(k,pointwise[j],j)] for j in range(3)]
    	ifftpwo=[[mi[j][k]*x%primess[j] for x in ifft(k,pointwiso[j],j)] for j in range(3)]
    
 	#H1=[chinese_remainder([ifftpwe[0][i],ifftpwe[1][i],ifftpwe[2][i]]) for i in xrange((lf-1)/2+1)]
    	#H2=[chinese_remainder([ifftpwo[0][i],ifftpwo[1][i],ifftpwo[2][i]]) for i in xrange((lf-1)/2+1)]
    
    	for i in range(1+(lf-1)//2):
            H[2*i]=chinese_remainder([ifftpwe[0][i],ifftpwe[1][i],ifftpwe[2][i]])
            H[2*i+1]=chinese_remainder([ifftpwo[0][i],ifftpwo[1][i],ifftpwo[2][i]])
    #hn=addpolymod(ResH,multpoly(fn, gn))[:lf]  
    hn=addpolymod(ResH,H)     
    s=[infact[i]*hn[lf-1-i]%P for i in range(lf)]
       
    #---Here, the polynomial f only has even degree terms. 
    #---In the expansion f(x+ sqrt t) = A(x) + sqrt t B(x), 
    #---A(x) has even degree terms, B(x) has odd degree terms 
    #---so A(x)=a(x^2), B(x)=x b(x^2)
    #---Returns A(x)^2 - t B(x)^2 by computing
    #---a(x^2)^2 - t x^2 b(x^2)^2
      
    g=s[0::2]
    h=s[1::2]
    ResA=addpolymod([0]*(lf-1)+[g[-1]*g[-1]%P],[0]*((lf-1)//2)+[2*g[i]*g[-1]%P for i in range((lf-1)//2)])     
    del g[-1]
    a=addpolymod(ResA,squarepoly(g))
    b=[0]+squarepoly(h)    
    c=[0]*(2*len(a)-1)
    b+=[0]*(len(a)-len(b))
    for i in range(len(a)):
            c[2*i]=(a[i]-t*b[i]%P)%P
    return c
 
#---Iteration steps--- 
 
def minpolymod(n):
    f=[-n[0]%P,0,1]
    for i in range(1,len(n)):       
        f=ftrans(f,n[i])
    return f
    
#---Main---           
    
T=int(input())
for i in range(T):
    n=int(input())
    a = list(map(int, input().split()))
    print(m[n])
    print(" ".join(str(x) for x in minpolymod(a)))     