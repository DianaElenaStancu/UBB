"""6. Găsește cel mai mic număr m din șirul lui Fibonacci definit de
 f[0]=f[1]=1, f[n]=f[n-1]+f[n-2], pentru n>2,
 mai mare decât numărul natural n dat, deci exista k astfel ca f[k]=m si m>n."""


def fibonacci(a, b):
    if a > n:
        return a
    return fibonacci(b, a + b)


n = int(input())
print(fibonacci(0, 1))
