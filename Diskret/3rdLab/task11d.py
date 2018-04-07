def func(cur,end):
    if(end-1==n):
        return
    for i in range(n):
        if(a[i]!=0):
            output.write(str(a[i]))
            output.write(' ')
    output.write('\n')
    for i in range(end+1,n+1):
        a[cur]=i
        func(cur+1,i)
        a[cur]=0

input=open('subsets.in', 'r')
output=open('subsets.out', 'w')
n=int(input.read())
a=[]
for i in range(n):
    a.append(0)
func(0,0)
