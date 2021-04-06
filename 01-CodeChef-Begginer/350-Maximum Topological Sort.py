from sys import setrecursionlimit
setrecursionlimit(10**6)

MOD=10**9+7

def dfscent(adj,v,par,n,centroid,sz):
    sz[v]=1
    iscentroid=True
    for a in adj[v]:
        if(a!=par):
            dfscent(adj,a,v,n,centroid,sz)
            sz[v]+=sz[a]
            if(sz[a]>n/2): 
                iscentroid=False
    if (n-sz[v])>n/2:
        iscentroid=False
    if(iscentroid):
        centroid.append(v)

def findCentroid(adj,n,sz):
    centroid=[]
    dfscent(adj,0,-1,n,centroid,sz)
    return max(centroid)
    

def topoval(adj,v,par,dp,sz):
    dp[v]=1
    sz[v]=1
    #print('Entering',v,par)
    for a in adj[v]:
        if(a!=par):
            topoval(adj,a,v,dp,sz)
            dp[v]=(dp[v]*dp[a])%MOD
            dp[v]=(dp[v]*invfact[sz[a]])%MOD
            sz[v]+=sz[a]
    #        print('Updating ',v,'with',a,dp[a],'dividing',sz[a],'value now',dp[v])
            
    dp[v]=(dp[v]*fact[sz[v]-1])%MOD
    #print('final Updating ',v,'multiplying',sz[v]-1)
    return dp[v]%MOD
    
fact = [1] * (5 * (10 ** 5) + 10)
invfact = [1] * (5 * (10 ** 5) + 10)
for i in range(1, len(fact)):
    fact[i] = (fact[i - 1] * i) % MOD
    invfact[i] = pow(fact[i], MOD - 2, MOD)
 
for _ in range(int(input())):
    n,k=map(int,input().split())
    adj=[[] for _ in range(int(n))]
    for _ in range(int(n-1)):
        u,v=map(int,input().split())
        adj[u-1].append(v-1)
        adj[v-1].append(u-1)
    
    sz=[0]*n
    first=findCentroid(adj,n,sz)
    dp=[-1]*n
    firstans=topoval(adj,first,-1,dp,sz)
    
    if(k==1):
        print(first+1,firstans)
    else:
        second=adj[first][0]
        for v in adj[first]:
            if(sz[v]>sz[second]):
                second=v
            if(sz[v]==sz[second] and v>second):
                second=v
        #print("going second with",second)
        secondans=topoval(adj,second,-1,dp,sz)
        print(second+1,secondans)
    