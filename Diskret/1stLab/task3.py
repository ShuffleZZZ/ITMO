def save1(c):
    if (c[-1]=='1'):
        return 1
    return 0

def save0(c):
    if (c[0]=='0'):
        return 1
    return 0


def dv(c, n):
    if (n==0):
        return 0
    for i in range(2**(n-1)):
        if (c[i]==c[-i-1]):
            return 0
    return 1


def mono(c,n):
    if n==0:
        return 1
    l = c[:2**(n-1)]
    r = c[2**(n-1):]
    for i in range(2**(n-1)):
        if (l[i]=='1' and r[i]=='0'):
            return 0
    return mono(l,n-1) and mono(r,n-1)


def line(c, n):
    tr = list(map(int,c))
    for i in range(1,2**n):
        for j in range(2**n-1,i-1,-1):
            tr[j] =(tr[j]+tr[j-1])%2
    st=[0,1,2,4,8,16,32]
    for i in range(2**n):
        if tr[i]==1 and not i in st:
            return 0
    return 1


n =int(input())
arr=list()
for i in range(n):
    arr.append(input().split())
    arr[i][0]=int(arr[i][0])
k1=0
k2=0
k3=0
k4=0
k5=0
for i in range(n):
    if (save1(arr[i][1])==0):
        k1=1
    if (save0(arr[i][1])==0):
        k2=1
    if (dv(arr[i][1],arr[i][0])==0):
        k3=1
    if (mono(arr[i][1],arr[i][0])==0):
        k4=1
    if (line(arr[i][1],arr[i][0])==0):
        k5=1
if (k1==k2==k3==k4==k5==1):
    print('YES')
else:
    print('NO')

