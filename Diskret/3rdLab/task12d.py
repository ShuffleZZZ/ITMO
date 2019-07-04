def func(cur,end):
    if (cur-1==n):
        if (end==0):
            for i in range(k):
                for j in range(1,n+1):
                    if (a[j]==i):
                        output.write(str(j)+' ')
                output.write('\n')
            output.write('\n')
            return
        else:
            return
    for i in range(k-end):
        a[cur]=i
        func(cur+1,end)
    a[cur]=k-end
    func(cur+1,end-1)
input = open('part2sets.in', 'r')
output = open('part2sets.out', 'w')
s=input.readline()
a=list(map(int,s.split()))
n=a[0]
k=a[1]
a.clear()
for i in range(20):
    a.append(0)
func(1,k)