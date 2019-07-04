def func(a,cur):
    if (cur<n):
        for i in range(1,n+1):
            if i not in a:
                a[cur]=i
                func(a,cur+1)
                a[cur]=0
    else:
        for i in range(n):
            output.write(str(a[i]))
            output.write(' ')
        output.write('\n')
input = open('permutations.in', 'r')
output = open('permutations.out', 'w')
n=int(input.read())
a=[]
for i in range(n):
    a.append(0)
func(a,0)
