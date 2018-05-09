def func(rootyasha):
    even=[]
    neven=[]
    if(dp[rootyasha]!=-10):
        return dp[rootyasha]
    for i in range (1,n+1):
        if (a[i]==rootyasha):
            even.append(i)
            for j in range(1,n+1):
                if(a[j]==i):
                    neven.append(j)
    s0=0
    s1=0
    if(len(neven)>0):
        for i in range(len(neven)):
            s1+=func(neven[i])
    if (len(even)>0):
        for i in range(len(even)):
            s0+=func(even[i])
    dp[rootyasha]=max(s1+1,s0)
    return dp[rootyasha]
n=int(input())
a=[-10]
dp=[-10]
for i in range (n):
    dp.append(-10)
    a.append(int(input()))
    if (a[i+1]==0):
        rootyasha=i+1
print(func(rootyasha))