def cautaZero(lista):
    if len(lista) == 0:
        return 0
    if lista[0] == 0:
        return 1
    return cautaZero(lista[1:])

l = [2,3,0,4]
print(cautaZero(l))

"""
n = 8
for i in range(n*n):
    print(i)

"""