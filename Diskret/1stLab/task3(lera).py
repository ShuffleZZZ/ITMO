def T1(f):
    if f[-1] == '1':
        return True
    return False

def T0(f):
    if f[0] == '0':
        return True
    return False

def M(f, n):
    if n == 0:
        return True
    l = f[:2**(n - 1)]
    r = f[2**(n - 1):]
    for i in range(2**(n - 1)):
        if l[i] == '1' and r[i] == '0':
            return False
    return M(l, n-1) and M(r, n-1)

def S(f, n):
    if n == 0:
        return False
    for i in range(2**(n-1)):
        if f[i] == f[-i-1]:
            return False
    return True

def L(f, n):
    b = list(map(int, f))
    for i in range(1, 2**n):
        for j in range(2**n-1, i-1, -1):
            b[j] = (b[j] + b[j - 1]) % 2
    st = [0, 1, 2, 4, 8, 16, 32]
    for i in range(2**n):
        if b[i] == 1 and not i in st:
            return False
    return True




n = int(input())
a = []
for i in range(n):
    a.append(input().split())
    a[i][0] = int(a[i][0])
c = [False]*5   
for i in range(n):
    if not T1(a[i][1]):
        c[0] = True
    if not T0(a[i][1]):
        c[1] = True    
    if  not S(a[i][1], a[i][0]):
        c[2] = True 
    if  not M(a[i][1], a[i][0]):
        c[3] = True
    if  not L(a[i][1], a[i][0]):
        c[4] = True

ok = True
for i in c:
    if i == 0:
        ok = False
        
if ok:
    print('YES')
else:
    print('NO')
    
    